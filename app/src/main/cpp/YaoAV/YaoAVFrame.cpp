#include "YaoAV.h"
#include "YaoAVFramePrivate.h"
extern "C"
{
#include <libavutil/pixdesc.h>
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
	printf("Channel: %d\n", channel);
	printf("nb_samples: %d\n", imp->frame->nb_samples);
	printf("sample_rate: %d\n", imp->frame->sample_rate);

	AVSampleFormat format = (AVSampleFormat)(imp->frame->format);

	char* str = (char*)malloc(128);
	str = av_get_sample_fmt_string(str, 128, format);

	printf("Sample Format: %s\n", str);

	free(str);

	for (int i = 0; i < AV_NUM_DATA_POINTERS; i++) {
		printf("Linesize[%d]: %d\n", i, imp->frame->linesize[i]);
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
