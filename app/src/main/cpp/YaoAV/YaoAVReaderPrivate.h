#pragma once
extern "C"
{
#include <libavformat/avformat.h>
}

class YaoAVReaderPrivate
{
public:
	AVFormatContext * formatContext = nullptr;
};