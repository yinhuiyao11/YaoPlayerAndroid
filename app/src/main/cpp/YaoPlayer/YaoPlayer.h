#pragma once

#include <string>
#include "../YaoGL/YaoGL.h"
#include "../YaoSL/YaoSL.h"
#include "YaoThread/YaoThread.h"
#include "YaoAV/YaoAV.h"
#include "YaoQueue/Queue.h"

enum YaoDecoderType
{
	YAODECODER_TYPE_VIDEO = 0,
	YAODECODER_TYPE_AUDIO = 1
};

enum YaoPlayerStatus
{
	YAOPLAYERSTATUS_PLAYING = 0,
	YAOPLAYERSTATUS_PAUSEING = 1
};

class YaoPlayerCtr : public YaoThread
{
public:
	YaoPlayerCtr(std::string _path, double _time = 0.0);
	~YaoPlayerCtr();

	virtual void run();

	int pushVideoFrameQueue(YaoAVFrame* avFrame);
	int pushAudioFrameQueue(YaoAVFrame* avframe);
	int getVideoFrameQueueSize();
	int getAudioFrameQueueSize();

	int play();
	int pause();

	int pushFrameplayVideoFrame(YaoAVFrame * frame);

	int pushFrameplayAudioFrame(YaoAVFrame * frame);
	int playAudioFrameSize();

public:
	double seekTime = 0.0;
    std::string path;
	YaoQueue<YaoAVFrame> playVideoFrameQueue;
	YaoQueue<YaoAVFrame> playAudioFrameQueue;
private:
	YaoQueue<YaoAVFrame> videoFrameQueue;
	YaoQueue<YaoAVFrame> audioFrameQueue;
	YaoPlayerStatus status = YaoPlayerStatus::YAOPLAYERSTATUS_PLAYING;

};

class YaoPlayerReaderThread : public YaoThread
{
public:
	YaoPlayerReaderThread(std::string _path, YaoPlayerCtr * ctr);
	~YaoPlayerReaderThread();
	virtual void run();

private:
	std::string path;
	YaoPlayerCtr * ctrThread = nullptr;
};

class YaoDecodeThread : public YaoThread
{
public:
	YaoDecodeThread(YaoPlayerCtr * ctr, YaoDecoderType type);
	~YaoDecodeThread();
	virtual void run();
	int init(YaoAVStream* stream);
	int pushPacket(YaoAVPacket * packet);
	int packetQueueSize();
private:
	Decoder * decode = nullptr;
	YaoQueue<YaoAVPacket> packetQueue;
	YaoPlayerCtr * ctrThread = nullptr;
	YaoDecoderType type;
};

class YaoPlayerGL
{
public:
    YaoPlayerGL(YaoQueue<YaoAVFrame> * playVideoFrameQueue);
    ~YaoPlayerGL();
    int surfaceChanged(int w, int h);
    int drawFrame();

public:
	YaoQueue<YaoAVFrame> * playVideoFrameQueueGL = nullptr;

private:
    //着色器程序
    YaoGLProgram * program = nullptr;
    YaoVAO * vao = nullptr;
};

class YaoPlayer
{
public:
	YaoPlayer(std::string path);
	~YaoPlayer();

	int open(double time = 0.0);
	int stop();
	int play();
	int pause();

	int seek(double time);

	int printQueueSize();

	int setWidthHeight();
	int getHeight();
	int getWidth();

	YaoPlayerGL * playerGl = nullptr;
	YaoSL * playerSl = nullptr;
	YaoPlayerCtr * playerCtr = nullptr;

private:
	std::string path;
	int height = 0;
	int width = 0;
};

