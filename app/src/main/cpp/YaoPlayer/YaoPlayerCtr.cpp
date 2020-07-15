#include "YaoPlayer.h"
#include "../EyerCore/EyerLog.hpp"

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
    EyerLog("=============================YaoPlayerCtr run \n");
    YaoPlayerReaderThread readerThread(path, this);
	readerThread.start();

	//��ȡ�߳�����ʱ��ʱ�� startTime
	long long startTime = YaoTime::getTime();
	YaoAVFrame* videoFrame = nullptr;
	YaoAVFrame* audioFrame = nullptr;
	long long pauseDurationAll = 0;

	//FILE* fout;
	//fout = fopen("/storage/emulated/0/ST/ads.yuv", "wb");

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
        EyerLog("++++videoFrameQueue.size:%d\n", getVideoFrameQueueSize());
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
				EyerLog("++++video frame videoFrame->getPts():%d, heigt:%d\n", videoFrame->getW(), videoFrame->getH());
				pushFrameplayVideoFrame(videoFrame);

				/*int width = videoFrame->getW();
				int height = videoFrame->getH();

				unsigned char* y;
				unsigned char* u;
				unsigned char* v;

				y = (unsigned char*)malloc(width * height);
				u = (unsigned char*)malloc(width / 2 * height / 2);
				v = (unsigned char*)malloc(width / 2 * height / 2);

				videoFrame->getY(y);
				videoFrame->getU(u);
				videoFrame->getV(v);

				fwrite(y, width * height, 1, fout);
				fwrite(u, width / 2 * height / 2, 1, fout);
				fwrite(v, width / 2 * height / 2, 1, fout);

				free(y);
				free(u);
				free(v);*/
				/*delete videoFrame;
				videoFrame = nullptr;*/
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

				/*delete audioFrame;
				audioFrame = nullptr;*/
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

int YaoPlayerCtr::pushFrameplayVideoFrame(YaoAVFrame * frame){
	return playVideoFrameQueue.push(frame);
}

int YaoPlayerCtr::playVideoFrameSize()
{
	return playVideoFrameQueue.queueSize();
}

int YaoPlayerCtr::pushFrameplayAudioFrame(YaoAVFrame * frame)
{
	return playAudioFrameQueue.push(frame);
}

int YaoPlayerCtr::playAudioFrameSize()
{
	return playAudioFrameQueue.queueSize();
}