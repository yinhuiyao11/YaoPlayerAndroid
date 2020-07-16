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

	//获取线程启动时的时间 startTime
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

		//获取当前时间 nowTime
		long long nowTime = YaoTime::getTime();
		//获取当前时间和开始时间的差 dTime
		long long dTime = nowTime - startTime;
		dTime = dTime - pauseDurationAll;
		dTime = dTime + (long long)(seekTime * 1000);
		//printf("dTime:%lld\n", dTime);
	
		//-------视频
		//从视频frame缓存队列中获取一帧视频 framePts
		if (videoFrame == nullptr) {
			videoFrameQueue.pop(&videoFrame);
		} 
        EyerLog("++++videoFrameQueue.size:%d\n", getVideoFrameQueueSize());
		if (videoFrame != nullptr) {
			//pts小于seektime，丢帧
			if (videoFrame->getPts() < (long long)(seekTime * 1000)) {
				delete videoFrame;
				videoFrame = nullptr;
			}
		}

        if (videoFrame != nullptr) {
            //如果 framePts <= dTime
			if (videoFrame->getPts() <= dTime) {
				//该帧立即播放
				EyerLog("++++video frame videoFrame->getPts():%lld, weight:%d, heigt:%d\n", videoFrame->getPts(), videoFrame->getW(), videoFrame->getH());
				pushFrameplayVideoFrame(videoFrame);

				YaoPlayer::playVideoFrameQueueStatic.push(videoFrame);
				EyerLog("===playVideoFrameQueueStatic size:%d\n", YaoPlayer::playVideoFrameQueueStatic.queueSize());
				delete videoFrame;
				videoFrame = nullptr;

			}
			else {
				//还不到播放的时间，程序自悬，或者去处理音频
			}
		}

		//------音频
		//从音频frame缓存队列中获取一帧音频 framePts
		if (audioFrame == nullptr) {
			audioFrameQueue.pop(&audioFrame);
		}
		//EyerLog("~~~audio.size:%d\n", getAudioFrameQueueSize());
		if (audioFrame != nullptr) {
            //如果 framePts <= dTime，
			if (audioFrame->getPts() <= dTime) {
				//该帧立即播放
				//EyerLog("~~~~~~~~audio frame audioFrame->getPts():%lld\n", audioFrame->audioPrint());
				pushFrameplayAudioFrame(audioFrame);

				delete audioFrame;
				audioFrame = nullptr;
			}
			else
			{
				//还不到播放的时间，程序自悬
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

YaoQueue<YaoAVFrame> * YaoPlayerCtr::getPlayVideoFrameQ()
{
    return  &playVideoFrameQueue;
}
