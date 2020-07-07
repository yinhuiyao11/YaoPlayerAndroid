#include "YaoPlayer.h"

YaoPlayerCtr::YaoPlayerCtr(double _time)
{
	seekTime = _time;
}

YaoPlayerCtr::~YaoPlayerCtr()
{

}

void YaoPlayerCtr::run()
{
	YaoPlayerReaderThread readerThread("c:/video/the5MP4.mp4", this);
	readerThread.start();

	//��ȡ�߳�����ʱ��ʱ�� startTime
	long long startTime = YaoTime::getTime();
	YaoAVFrame* videoFrame = nullptr;
	YaoAVFrame* audioFrame = nullptr;
	long long pauseDurationAll = 0;
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
				printf("video frame videoFrame->getPts():%lld\n", videoFrame->getPts());
				delete videoFrame;
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
		if (audioFrame != nullptr) {
			//��� framePts <= dTime��
			if (audioFrame->getPts() <= dTime) {
				//��֡��������
				//printf("audio frame audioFrame->getPts():%lld\n", audioFrame->getPts());

				delete audioFrame;
				audioFrame = nullptr;
			}
			else
			{
				//���������ŵ�ʱ�䣬��������
			}
		}

	}

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