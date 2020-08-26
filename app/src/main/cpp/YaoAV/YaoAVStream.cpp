#include "YaoAVStreamPrivate.h"
#include "YaoAV.h"

YaoAVStream::YaoAVStream()
{
	imp = new YaoAVStreamPrivate();
	imp->codecpar = avcodec_parameters_alloc();
}

YaoAVStream::~YaoAVStream()
{
	if (imp->codecpar != nullptr) {
		avcodec_parameters_free(&imp->codecpar);
		imp->codecpar = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int YaoAVStream::scalePacketPts(YaoAVPacket & pkt)
{
	uint64_t pts = pkt.getPTS();
	double ptsSec = pts * 1.0 * timebaseNum / timebaseDen;
	pkt.secPTS = ptsSec;
	return 0;
}

int YaoAVStream::getHeight()
{
	return imp->codecpar->height;
}

int YaoAVStream::getWidth()
{
	return imp->codecpar->width;
}
