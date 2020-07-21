#include "YaoThread.h"

int YaoThread::start()
{
	if (t == nullptr) {
		stopFlag = 0;
		t = new std::thread(&YaoThread::run, this);
	}
	return 0;
}

int  YaoThread::stop()
{
	if (t != nullptr) {
		stopFlag = 1;
		t->join();
		delete t;
		t = nullptr;
	}
	return 0;
}
