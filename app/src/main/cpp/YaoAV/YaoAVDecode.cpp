#include "YaoAV.h"
#include "YaoAVDecodeContextPrivate.h"
#include "YaoAVStreamPrivate.h"
#include "YaoAVPacketPrivate.h"
#include "YaoAVFramePrivate.h"

Decoder::Decoder() {
	imp = new YaoAVDecodePrivate();
	imp->codecContext = avcodec_alloc_context3(nullptr);
}
Decoder::~Decoder() 
{
	if (imp->codecContext != nullptr) {
		avcodec_free_context(&imp->codecContext);
		imp->codecContext = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int Decoder::init(YaoAVStream* stream)
{
	timebaseDen = stream->timebaseDen;
	timebaseNum = stream->timebaseNum;
	avcodec_parameters_to_context(imp->codecContext, stream->imp->codecpar);
	AVCodec * codec = avcodec_find_decoder(imp->codecContext->codec_id);
	int ret = avcodec_open2(imp->codecContext, codec, nullptr);
	if (ret) {
		printf("Open Decoder Fail:%d\n", ret);
		return -1;
	}
	return 0;
}

int Decoder::sendPacket(YaoAVPacket* packet)
{
	int ret = 0;
	if (packet == nullptr) {
		ret = avcodec_send_packet(imp->codecContext, nullptr);
	}
	else {
		ret = avcodec_send_packet(imp->codecContext, packet->packetPrivate->packet);
	}
	return ret;
}

int Decoder::receiveFrame(YaoAVFrame* frame)
{
	int ret = avcodec_receive_frame(imp->codecContext, frame->imp->frame);
	if (!ret) {
		//将秒级时间戳计算
		frame->imp->pts_sec = frame->imp->frame->pts * 1.0 * timebaseNum / timebaseDen;
	}
	return ret;
}

int Decoder::close()
{
	return avcodec_close(imp->codecContext);
}
