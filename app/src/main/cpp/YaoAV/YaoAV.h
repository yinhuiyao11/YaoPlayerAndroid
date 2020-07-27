#pragma once

class YaoAVPacketPrivate;
class YaoAVReaderPrivate;
class YaoAVStreamPrivate;
class YaoAVDecodePrivate;
class YaoAVFramePrivate;
class YaoAVStream;

class YaoAVPacket
{
public:
	YaoAVPacket();
	~YaoAVPacket();
public:
	YaoAVPacketPrivate * packetPrivate = nullptr;
	int getIndex();
};

class YaoAVFrame
{
public:
	YaoAVFrame();
	~YaoAVFrame();
	int videoPrint();
	int audioPrint();
	int getW();
	int getH();
	int getY(unsigned char * y);
	int getU(unsigned char * u);
	int getV(unsigned char * v);

	int getChannels();
	int getNBSamples();
	int getPerSampleSize();
	int getAudioData(unsigned char * data);
	int getAudioPackedData(unsigned char * data);

	long long getPts();
public:
	YaoAVFramePrivate* imp = nullptr;
};

class YaoAVReader
{
public:
	YaoAVReader();
	~YaoAVReader();

	int Open(const char * path);
	int Close();
	int Read(YaoAVPacket * packet);
	int getStreamCount();
	int getStream(YaoAVStream * stream, int streamIndex);

	int getVideoStreamIndex();
	int getAudioStreamIndex();

	int seek(double time);
private:
	YaoAVReaderPrivate * formatContextPrivate = nullptr;
};

class YaoAVStream
{
public:
	YaoAVStream();
	~YaoAVStream();
public:
	YaoAVStreamPrivate* imp = nullptr;
	int streamIndex = -1;
	int timebaseDen = -1;
	int timebaseNum = -1;
};

class Decoder
{
public:
	YaoAVDecodePrivate* imp = nullptr;
	int timebaseDen = -1;
	int timebaseNum = -1;
public:
	Decoder();
	~Decoder();

	int init(YaoAVStream* stream);
	int sendPacket(YaoAVPacket * packet);
	int receiveFrame(YaoAVFrame * frame);
	int close();
};

class YaoTime
{
public:
	static long long getTime();
};

