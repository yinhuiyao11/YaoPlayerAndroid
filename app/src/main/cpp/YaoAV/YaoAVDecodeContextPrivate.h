#pragma once
extern "C"
{
#include <libavformat/avformat.h>
}

class YaoAVDecodePrivate {
public:
	AVCodecContext * codecContext = nullptr;
};