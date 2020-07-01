#pragma once
extern "C"
{
#include <libavformat/avformat.h>
}

class YaoAVStreamPrivate {
public:
	AVCodecParameters* codecpar = nullptr;
};