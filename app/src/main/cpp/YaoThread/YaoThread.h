#include <stdio.h>
#include <thread>

class YaoThread {
public:
	virtual void run() = 0;
	int start();
	int stop();
public:
	std::thread * t = nullptr;
	int stopFlag = 0;
};