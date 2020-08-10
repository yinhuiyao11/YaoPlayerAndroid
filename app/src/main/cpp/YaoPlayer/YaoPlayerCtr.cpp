#include "YaoPlayer.h"
#include "../EyerCore/EyerLog.hpp"
#include "YaoPlayerJni/JavaVMObj.h"


YaoPlayerCtr::YaoPlayerCtr(std::string _path, double _time)
{
    path = _path;
    seekTime = _time;
}

YaoPlayerCtr::~YaoPlayerCtr()
{

}

void YaoPlayerCtr::run()
{
    YaoPlayerReaderThread readerThread(path, this);
	readerThread.start();

	//��ȡ�߳�����ʱ��ʱ�� startTime
	long long startTime = YaoTime::getTime();
	YaoAVFrame* videoFrame = nullptr;
	YaoAVFrame* audioFrame = nullptr;
	long long pauseDurationAll = 0;

	while(readerThread.getAudioSampleRate() == 0 || readerThread.getAudioChannels() == 0){
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	//EyerLog("++++++++++++getAudioSampleRate:%d ,getAudioChannels:%d ",reader.getAudioSampleRate(), reader.getAudioChannels());
	YaoSL playerSl(&playAudioFrameQueue);
	//1 ��������
	playerSl.createEngin();
	//2 ����������
	playerSl.createMix();
	//3 ������Ƶ��Ϣ
	playerSl.setDataSource(10, readerThread.getAudioSampleRate(), readerThread.getAudioChannels());
	// 4 ����������
	playerSl.createAudioPlayer();

	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		long long pauseStart = YaoTime::getTime();
		while (status == YaoPlayerStatus::YAOPLAYERSTATUS_PAUSEING)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		long long pauseEnd = YaoTime::getTime();
		long long pauseDuration = pauseEnd - pauseStart;
		pauseDurationAll += pauseDuration;

		//��ȡ��ǰʱ�� nowTime
		long long nowTime = YaoTime::getTime();
		//��ȡ��ǰʱ��Ϳ�ʼʱ��Ĳ� dTime
		long long dTime = nowTime - startTime;
		dTime = dTime - pauseDurationAll;
		dTime = dTime + (long long)(seekTime * 1000);
		//printf("dTime:%lld\n", dTime);
	
		//-------��Ƶ
		//����Ƶframe��������л�ȡһ֡��Ƶ framePts
		if (videoFrame == nullptr) {
			videoFrameQueue.pop(&videoFrame);
		} 
        //EyerLog("++++videoFrameQueue.size:%d\n", getVideoFrameQueueSize());
		if (videoFrame != nullptr) {
			//ptsС��seektime����֡

            if (videoFrame->getPts() < (long long)(seekTime * 1000)) {
                delete videoFrame;
				videoFrame = nullptr;
			}
		}

        if (videoFrame != nullptr) {
            //��� framePts <= dTime
			if (videoFrame->getPts() <= dTime) {
				//��֡��������
				//EyerLog("++++video frame videoFrame->getPts():%lld, weight:%d, heigt:%d\n", videoFrame->getPts(), videoFrame->getW(), videoFrame->getH());
				pushFrameplayVideoFrame(videoFrame);

                videoFrame = nullptr;
			}
			else {
				//���������ŵ�ʱ�䣬��������������ȥ������Ƶ
			}
		}

		//------��Ƶ
		//����Ƶframe��������л�ȡһ֡��Ƶ framePts
		if (audioFrame == nullptr) {
			audioFrameQueue.pop(&audioFrame);
		}
		//EyerLog("~~~audio.size:%d\n", getAudioFrameQueueSize());
		if (audioFrame != nullptr) {
            //��� framePts <= dTime��
			if (audioFrame->getPts() <= dTime) {
				//��֡��������
				//EyerLog("~~~~~~~~audio frame audioFrame->getPts():%lld\n", audioFrame->audioPrint());
				pushFrameplayAudioFrame(audioFrame);

				//delete audioFrame;
				audioFrame = nullptr;
			}
			else
			{
				//���������ŵ�ʱ�䣬��������
			}
		}

	}
	EyerLog("1111111 to the end\n");

	JNIEnv *env = NULL;
	JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);

	jclass clazz = env->FindClass("com/yao/yaoplayerandroid/player/PlayEndCallback");
	if(clazz == NULL){
		EyerLog("~~~~~~~~~~clazz is null \n");
	}
	jmethodID onCall = env->GetStaticMethodID(clazz, "onEndCallBack","()I");
	if(onCall == NULL){
		EyerLog("~~~~~~~~~~onCall is null \n");
	} else{
        EyerLog("~~~~~~~~~~onCall is not null \n");

    }
	env->CallStaticIntMethod(clazz, onCall);
	
	readerThread.stop();

}

int YaoPlayerCtr::pushVideoFrameQueue(YaoAVFrame* avFrame)
{
	return videoFrameQueue.push(avFrame);
}

int YaoPlayerCtr::pushAudioFrameQueue(YaoAVFrame* avframe)
{
	return audioFrameQueue.push(avframe);
}

int YaoPlayerCtr::getVideoFrameQueueSize()
{
	return videoFrameQueue.queueSize();
}

int YaoPlayerCtr::getAudioFrameQueueSize()
{
	return audioFrameQueue.queueSize();
}

int YaoPlayerCtr::play()
{

	status = YaoPlayerStatus::YAOPLAYERSTATUS_PLAYING;
	return 0;
}

int YaoPlayerCtr::pause()
{
	status = YaoPlayerStatus::YAOPLAYERSTATUS_PAUSEING;
	return 0;
}

int YaoPlayerCtr::pushFrameplayVideoFrame(YaoAVFrame * frame){
	return playVideoFrameQueue.push(frame);
}

int YaoPlayerCtr::pushFrameplayAudioFrame(YaoAVFrame * frame)
{
	return playAudioFrameQueue.push(frame);
}

int YaoPlayerCtr::playAudioFrameSize()
{
	return playAudioFrameQueue.queueSize();
}


