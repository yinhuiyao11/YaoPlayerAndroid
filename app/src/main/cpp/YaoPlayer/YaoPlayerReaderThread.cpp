#include <cpp/EyerCore/EyerLog.hpp>
#include "YaoPlayer.h"
#include "YaoAV/YaoAV.h"
#include "../EyerCore/EyerLog.hpp"
#include "../YaoPlayerJni/JavaVMObj.h"

extern "C"
{
#include <libavutil/error.h>
#include <libavutil/avutil.h>
}

YaoPlayerReaderThread::YaoPlayerReaderThread(std::string _path, YaoPlayerCtr* _ctrThread)
{
	path = _path;
	ctrThread = _ctrThread;
}
YaoPlayerReaderThread::~YaoPlayerReaderThread()
{
}

void YaoPlayerReaderThread::run()
{
	YaoAVReader reader;
	int ret = reader.Open(path.c_str());
	if (ret) {
		EyerLog("=============================read file fail , %s, %d\n", path.c_str(), ret);
		return;
	}

	audioChannels = reader.getAudioChannels();
	audioSampleRate = reader.getAudioSampleRate();
	EyerLog("++++++++++++getAudioSampleRate:%d ,getAudioChannels:%d ",reader.getAudioSampleRate(), reader.getAudioChannels());

	reader.seek(ctrThread->seekTime);
	EyerLog("=============================YaoPlayerReaderThread getStreamCount: %d\n", reader.getStreamCount());

	int videoStreamIndex = reader.getVideoStreamIndex();
	int audioStreamIndex = reader.getAudioStreamIndex();

	//TODO��ʼ��������
	YaoDecodeThread* videoDecodeThread = new  YaoDecodeThread(ctrThread, YaoDecoderType::YAODECODER_TYPE_VIDEO);
	YaoDecodeThread* audioDecodeThread = new  YaoDecodeThread(ctrThread, YaoDecoderType::YAODECODER_TYPE_AUDIO);

	YaoAVStream videoStream;
	reader.getStream(&videoStream, videoStreamIndex);
	videoDecodeThread->init(&videoStream);

	YaoAVStream audioStream;
	reader.getStream(&audioStream, audioStreamIndex);
	audioDecodeThread->init(&audioStream);

	videoDecodeThread->start();
	audioDecodeThread->start();

	while (!stopFlag) {
		if (videoDecodeThread->packetQueueSize() > 5 && audioDecodeThread->packetQueueSize() > 5) {
			continue;
		}

		YaoAVPacket * pkt = new YaoAVPacket();
		int ret = reader.Read(pkt);
        if(ret == AVERROR_EOF){
			JavaVMObj obj;
			obj.callJavaMethod(JavaVMObj::jobj, "playEndCallback","()I");

        }
		if (ret) {
			delete pkt;
			pkt = nullptr;
			break;
		}

		if (pkt->getIndex() == videoStreamIndex) {
			videoDecodeThread->pushPacket(pkt);
		}

		if (pkt->getIndex() == audioStreamIndex) {
			audioDecodeThread->pushPacket(pkt);
		}
		//��packet���뻺��
		//printf("get packet\n");

	}

	videoDecodeThread->stop();
	audioDecodeThread->stop();
	reader.Close();
}

int YaoPlayerReaderThread::getAudioSampleRate()
{
	return  audioSampleRate;
}

int YaoPlayerReaderThread::getAudioChannels()
{
	return audioChannels;
}