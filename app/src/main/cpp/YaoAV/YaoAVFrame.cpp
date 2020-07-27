#include "YaoAV.h"
#include "YaoAVFramePrivate.h"
#include "../EyerCore/EyerLog.hpp"
extern "C"
{
#include <libavutil/pixdesc.h>
#include <libswresample/swresample.h>
}

YaoAVFrame::YaoAVFrame() 
{
	imp = new YaoAVFramePrivate();
	imp->frame = av_frame_alloc();
}

YaoAVFrame::~YaoAVFrame()
{
	if (imp->frame != nullptr) {
		av_frame_free(&imp->frame);
		imp->frame = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int YaoAVFrame::videoPrint()
{
	printf("width: %d \n", imp->frame->width);
	printf("height: %d \n", imp->frame->height);
	AVPixelFormat pixelFormat = (AVPixelFormat)imp->frame->format;
	char* buf = (char*)malloc(128);
	av_get_pix_fmt_string(buf, 128, pixelFormat);
	printf("Pix format: %s \n", buf);
	free(buf);
	for (int i = 0; i < AV_NUM_DATA_POINTERS; i++) {
		printf("linesize[%d]: %d \n", i, imp->frame->linesize[i]);
	}

	return 0;
}

int YaoAVFrame::audioPrint()
{
	int channel = imp->frame->channels;
	EyerLog("Channel: %d\n", channel);
	EyerLog("nb_samples: %d\n", imp->frame->nb_samples);
	EyerLog("sample_rate: %d\n", imp->frame->sample_rate);

	AVSampleFormat format = (AVSampleFormat)(imp->frame->format);

	char* str = (char*)malloc(128);
	str = av_get_sample_fmt_string(str, 128, format);

	EyerLog("Sample Format: %s\n", str);

	free(str);

	for (int i = 0; i < AV_NUM_DATA_POINTERS; i++) {
		EyerLog("Linesize[%d]: %d\n", i, imp->frame->linesize[i]);
    }
	return 0;
}

int YaoAVFrame::getW()
{
	return imp->frame->width;
}

int YaoAVFrame::getH()
{
	return imp->frame->height;
}

int YaoAVFrame::getY(unsigned char* y)
{
	int height = getH();
	int width = getW();
	for (int i = 0; i < height; i++) {
		memcpy(y + width * i, imp->frame->data[0] + imp->frame->linesize[0] * i, width);
	}
	return 0;
}

int YaoAVFrame::getU(unsigned char* u)
{
	int height = getH() / 2;
	int width = getW() / 2;
	for (int i = 0; i < height; i++) {
		memcpy(u + width * i, imp->frame->data[1] + imp->frame->linesize[1] * i, width);
	}
	return 0;
}

int YaoAVFrame::getV(unsigned char* v) 
{
	int height = getH() /2;
	int width = getW() /2;
	for (int i = 0; i < height; i++) {
		memcpy(v + width * i, imp->frame->data[2] + imp->frame->linesize[2] * i, width);
	}
	return 0;
}

long long YaoAVFrame::getPts()
{
	return (long long)(imp->pts_sec * 1000);
}

int YaoAVFrame::getChannels()
{
	return imp->frame->channels;
}

//单个声道中包含的采样点数
int YaoAVFrame::getNBSamples()
{
	return  imp->frame->nb_samples;
}

//获取每个sample中的字节数
int YaoAVFrame::getPerSampleSize()
{
	return av_get_bytes_per_sample((AVSampleFormat)imp->frame->format);
}

int YaoAVFrame::getAudioData(unsigned char * data)
{
	int perChannelsByte = getPerSampleSize() * getNBSamples();
	for(int i=0; i<getChannels(); i++){
		memcpy(data + perChannelsByte * i, imp->frame->data[i], perChannelsByte);
	}
	return 0;
}

int YaoAVFrame::getAudioPackedData(unsigned char * data){
    int sizePerSample = getPerSampleSize();
    int bufferSize = sizePerSample * getNBSamples() * getChannels();
    if(data == nullptr){
        return bufferSize;
    }

    // 判断是 Packed 还是 Plane
    int isPanar = av_sample_fmt_is_planar((AVSampleFormat)imp->frame->format);
    if(isPanar){
        EyerLog("Panar\n");
        SwrContext * swrCtx = swr_alloc_set_opts(
                NULL,
                imp->frame->channel_layout,
                // av_get_packed_sample_fmt((AVSampleFormat)imp->frame->format),
				AVSampleFormat::AV_SAMPLE_FMT_S32,
                imp->frame->sample_rate,

                imp->frame->channel_layout,
                (AVSampleFormat)imp->frame->format,
                imp->frame->sample_rate,

                0,
                NULL
        );


        swr_init(swrCtx);

        int ret = swr_convert(swrCtx, &data, imp->frame->nb_samples, (const uint8_t **)imp->frame->data, imp->frame->nb_samples);

        swr_free(&swrCtx);
    }
    else{
        EyerLog("Packed\n");
        memcpy(data, imp->frame->data[0], bufferSize);
    }

    return 0;
}
