#include "EyerCore/EyerLog.hpp"
#include "YaoAV.h"
#include "YaoAVReaderPrivate.h"
#include "YaoAVPacketPrivate.h"
#include "YaoAVStreamPrivate.h"

YaoAVReader::YaoAVReader()
{
	av_register_all();
	avformat_network_init();
	formatContextPrivate = new YaoAVReaderPrivate();
	formatContextPrivate->formatContext = avformat_alloc_context();
}

YaoAVReader::~YaoAVReader()
{
	if (formatContextPrivate->formatContext != nullptr) {
		avformat_free_context(formatContextPrivate->formatContext);
		formatContextPrivate->formatContext = nullptr;
	}
}

int YaoAVReader::Open(const char* path)
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	int ret = avformat_open_input(&formatContextPrivate->formatContext, path, nullptr, nullptr);
	if (!ret) {
		avformat_find_stream_info(formatContextPrivate->formatContext, nullptr);
	}
	return ret;
}

int YaoAVReader::Close()
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	avformat_close_input(&formatContextPrivate->formatContext);
	return 0;
}

int YaoAVReader::Read(YaoAVPacket* packet)
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	int ret = av_read_frame(formatContextPrivate->formatContext, packet->packetPrivate->packet);
	return ret;
}

int YaoAVReader::getStreamCount()
{
	return formatContextPrivate->formatContext->nb_streams;
}
int YaoAVReader::getStream(YaoAVStream* yaoStream, int streamIndex)
{
	AVStream * avStream = formatContextPrivate->formatContext->streams[streamIndex];
	yaoStream->streamIndex = avStream->index;
	yaoStream->timebaseDen = avStream->time_base.den;
	yaoStream->timebaseNum = avStream->time_base.num;

	return avcodec_parameters_copy(yaoStream->imp->codecpar, avStream->codecpar);
}

int  YaoAVReader::getVideoStreamIndex()
{
	return av_find_best_stream(formatContextPrivate->formatContext, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
}

int  YaoAVReader::getAudioStreamIndex()
{
	return av_find_best_stream(formatContextPrivate->formatContext, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
}

int YaoAVReader::seek(double time)
{
	if (formatContextPrivate->formatContext == nullptr) {
		return -1;
	}
	int64_t timestamp = (int64_t)(time * AV_TIME_BASE);
	av_seek_frame(formatContextPrivate->formatContext, -1, timestamp, AVSEEK_FLAG_BACKWARD);
	return 0;
}

int YaoAVReader::getVideoWidth()
{
	AVStream * avStream = formatContextPrivate->formatContext->streams[getVideoStreamIndex()];
	return avStream->codec->width;
}

int YaoAVReader::getVideoHeight()
{
	AVStream * avStream = formatContextPrivate->formatContext->streams[getVideoStreamIndex()];
	return avStream->codec->height;
}

int YaoAVReader::getAudioSampleRate()
{
	AVStream * avStream = formatContextPrivate->formatContext->streams[getAudioStreamIndex()];
	return avStream->codec->sample_rate;
}

int YaoAVReader::getAudioChannels()
{
	AVStream * avStream = formatContextPrivate->formatContext->streams[getAudioStreamIndex()];
	return avStream->codec->channels;
}

