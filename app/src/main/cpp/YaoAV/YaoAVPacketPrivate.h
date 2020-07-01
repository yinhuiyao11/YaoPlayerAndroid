#pragma once
extern "C"
{
#include <libavformat/avformat.h>
}

class YaoAVPacketPrivate {
public:
	AVPacket * packet = nullptr;
};