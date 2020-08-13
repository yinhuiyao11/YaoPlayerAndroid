#include "YaoPlayer.h"
#include "../EyerCore/EyerLog.hpp"
#include "../YaoPlayerJni/JavaVMObj.h"

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

	//获取线程启动时的时间 startTime
	long long startTime = YaoTime::getTime();
	YaoAVFrame* videoFrame = nullptr;
	YaoAVFrame* audioFrame = nullptr;
	long long pauseDurationAll = 0;

	//进度回调函数调用次数
	int callbackNum = 0;

	while(readerThread.getAudioSampleRate() == 0 || readerThread.getAudioChannels() == 0){
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	//EyerLog("++++++++++++getAudioSampleRate:%d ,getAudioChannels:%d ",reader.getAudioSampleRate(), reader.getAudioChannels());
	YaoSL playerSl(&playAudioFrameQueue);
	//1 创建引擎
	playerSl.createEngin();
	//2 创建混音器
	playerSl.createMix();
	//3 配置音频信息
	playerSl.setDataSource(10, readerThread.getAudioSampleRate(), readerThread.getAudioChannels());
	// 4 创建播放器
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
        //EyerLog("++++videoFrameQueue.size:%d\n", getVideoFrameQueueSize());
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
				//EyerLog("++++video frame videoFrame->getPts():%lld, weight:%d, heigt:%d\n", videoFrame->getPts(), videoFrame->getW(), videoFrame->getH());
				pushFrameplayVideoFrame(videoFrame);

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

				//delete audioFrame;
				audioFrame = nullptr;
			}
			else
			{
				//还不到播放的时间，程序自悬
			}
		}

		//每隔一秒调用进度回调函数，传入dtime

		if(dTime > 1000 * callbackNum) {
			JavaVMObj obj;
			obj.callJavaMethod(JavaVMObj::jobj, "playSetProgressBar", "(I)I", (int)(dTime/1000));
			callbackNum++;
		}
	}
	//EyerLog("1111111 to the end\n");

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


