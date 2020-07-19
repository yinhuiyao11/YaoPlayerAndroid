#include "YaoPlayer.h"
#include "../EyerCore/EyerLog.hpp"
//YaoQueue<YaoAVFrame> YaoPlayer::playVideoFrameQueueStatic;

YaoPlayer::YaoPlayer(std::string _path)
{
	path = _path;
}

YaoPlayer::~YaoPlayer()
{
	if(playerGl != nullptr){
		delete playerGl;
		playerGl = nullptr;
	}
}

int YaoPlayer::open(double time)
{
	if (playerCtr == nullptr) {
		playerCtr = new YaoPlayerCtr(path, time);
		playerCtr->start();
		playerGl = new YaoPlayerGL(&(playerCtr->playVideoFrameQueue));
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

int YaoPlayer::printQueueSize() {
	if(&(playerCtr->playVideoFrameQueue) == nullptr){
		EyerLog("+++++++++++++++++++++++++++++playVideoFrameQueueGL is null\n");

	}
	EyerLog("+++++++++++++++++++++++++++++playVideoFrameQueueGL is not null\n");

	EyerLog("+++++++++++++++++++++++++++++playVideoFrameQueueGL->size:%d\n", playerCtr->playVideoFrameQueue.queueSize());
}
