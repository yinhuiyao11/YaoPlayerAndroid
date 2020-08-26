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

double YaoAVPacket::getSecPTS()
{
	//todo
	return 0;
}

unsigned char * YaoAVPacket::getDataPtr()
{
	return packetPrivate->packet->data;
}
