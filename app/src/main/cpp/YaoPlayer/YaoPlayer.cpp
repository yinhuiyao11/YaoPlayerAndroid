#include "YaoPlayer.h"
#include "../EyerCore/EyerLog.hpp"
#include "../YaoPlayerJni/JavaVMObj.h"
//YaoQueue<YaoAVFrame> YaoPlayer::playVideoFrameQueueStatic;

YaoPlayer::YaoPlayer(std::string _path)
{
	path = _path;
	setWidthHeight();
}

YaoPlayer::~YaoPlayer()
{
	if(playerGl != nullptr){
		delete playerGl;
		playerGl = nullptr;
	}
	if(playerSl != nullptr){
		delete playerSl;
		playerSl = nullptr;
	}
}

int YaoPlayer::open(double time)
{
	if (playerCtr == nullptr) {
		playerCtr = new YaoPlayerCtr(path, time);
		playerCtr->start();
		if(playerGl == nullptr){
			playerGl = new YaoPlayerGL(&(playerCtr->playVideoFrameQueue));
		}
		if(playerSl == nullptr){
			/*EyerLog("in playSL new \n");
			playerSl = new YaoSL(&(playerCtr->playAudioFrameQueue));
			//1 创建引擎
			playerSl->createEngin();
			//2 创建混音器
			playerSl->createMix();
			//3 配置音频信息
			EyerLog("++++++++++++audioSampleRate:%d ,audioChannels:%d ",audioSampleRate, audioChannels);

			playerSl->setDataSource(10, audioSampleRate, audioChannels);
			// 4 创建播放器
			playerSl->createAudioPlayer();
			EyerLog("in playSL end \n");*/

		}
		return 0;
	}
	return -1;
}

int YaoPlayer::stop()
{
	if (playerCtr != nullptr) {
		playerCtr->stop();
		delete playerCtr;
		playerCtr = nullptr;
	}
	return 0;
}

int YaoPlayer::play()
{
	return playerCtr->play();
}

int YaoPlayer::pause()
{
	return playerCtr->pause();
}

int YaoPlayer::seek(double time)
{
	stop();
	open(time);
	return 0;
}

int YaoPlayer::getHeight()
{
	return height;
}

int YaoPlayer::getWidth()
{
	return  width;
}

int YaoPlayer::setWidthHeight()
{
	YaoAVReader reader;
	int ret = reader.Open(path.c_str());
	if (ret) {
		EyerLog("=============================read file fail (setWidthHeight) , %s, %d\n", path.c_str(), ret);
		return -1;
	}
	height = reader.getVideoHeight();
	width = reader.getVideoWidth();
	duration = reader.getDuration();
	audioChannels = reader.getAudioChannels();
	audioSampleRate = reader.getAudioSampleRate();
	return 0;
}

long long YaoPlayer::getDuration()
{
	return duration;
}


int YaoPlayer::printQueueSize() {
	if(&(playerCtr->playVideoFrameQueue) == nullptr){
		EyerLog("+++++++++++++++++++++++++++++playVideoFrameQueueGL is null\n");

	}
	EyerLog("+++++++++++++++++++++++++++++playVideoFrameQueueGL is not null\n");

	EyerLog("+++++++++++++++++++++++++++++playVideoFrameQueueGL->size:%d\n", playerCtr->playVideoFrameQueue.queueSize());
    return 0;
}

