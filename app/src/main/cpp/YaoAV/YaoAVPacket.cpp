#include "YaoAV.h"
#include "YaoAVPacketPrivate.h"
YaoAVPacket::YaoAVPacket()
{
	packetPrivate = new YaoAVPacketPrivate();
	packetPrivate->packet = av_packet_alloc();
}

YaoAVPacket::~YaoAVPacket()
{
	if (packetPrivate->packet != nullptr) {
		av_packet_free(&packetPrivate->packet);
		packetPrivate->packet = nullptr;
	}
}

int YaoAVPacket::getIndex()
{
	return packetPrivate->packet->stream_index;
}

int YaoAVPacket::getSize()
{
	return packetPrivate->packet->size;
}

uint64_t YaoAVPacket::getPTS()
{
	return packetPrivate->packet->pts;
}


double YaoAVPacket::getSecPTS()
{
	return secPTS;
}

unsigned char * YaoAVPacket::getDataPtr()
{
	return packetPrivate->packet->data;
}
