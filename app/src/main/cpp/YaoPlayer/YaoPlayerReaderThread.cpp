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
            EyerLog("=============================in AVERROR_EOF\n");
            /*JavaVMObj javaVMObj;
            javaVMObj.callJavaStaticMethod();*/
			JNIEnv *env1 = NULL;
			JavaVMObj::javaVm->AttachCurrentThread(&env1, NULL);

			jclass clazz1 = env1->FindClass("com/yao/yaoplayerandroid/player/PlayEndCallback");
			if(clazz1 == NULL){
				EyerLog("~~~~~~~~~~clazz is null \n");
			}
			jmethodID onCall = env1->GetStaticMethodID(clazz1, "onEndCallBack","()I");
			if(onCall == NULL){
				EyerLog("~~~~~~~~~~onCall is null \n");
			} else{
				EyerLog("~~~~~~~~~~onCall is not null \n");

			}
			env1->CallStaticIntMethod(clazz1, onCall);
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