#include "YaoPlayer.h"

YaoPlayer::YaoPlayer(std::string _path)
{
	path = _path;
}

YaoPlayer::~YaoPlayer()
{

}

int YaoPlayer::open(double time)
{
	if (playerCtr == nullptr) {
		playerCtr = new YaoPlayerCtr(time);
		playerCtr->start();
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