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