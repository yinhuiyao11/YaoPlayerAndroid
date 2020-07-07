#pragma once

#include <queue>
#include <mutex>

/*
YaoQueue<YaoAVFrame>
YaoQueue<YaoAVPacket>
*/

template<typename T>
class YaoQueue
{
public:
	YaoQueue() 
	{

	}
	~YaoQueue() 
	{
		std::lock_guard<std::mutex> lck(mut);
		while (queueSize() > 0)
		{
			queue.pop();
		}
	}

	int push(T* t) {
		std::lock_guard<std::mutex> lck(mut);
		queue.push(t);
		return 0;
	}

	int queueSize() {
		return queue.size();
	}

	int pop(T* * t) {
		std::lock_guard<std::mutex> lck(mut);
		int size = queueSize();
		if (size > 0) {
			*t = queue.front();
			queue.pop();
			return 0;
		}
		return -1;
	}

private:
	std::queue<T *> queue;
	std::mutex mut;
};