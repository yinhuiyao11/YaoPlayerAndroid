#include <cpp/YaoPlayerJni/JavaVMObj.h>
#include <cpp/YaoCodec/YaoCodec.h>
#include "YaoPlayer.h"
#include "EyerCore/EyerLog.hpp"

YaoDecodeThread::YaoDecodeThread(YaoPlayerCtr* _ctrThread, YaoDecoderType _type)
{
	decode = new Decoder();
	ctrThread = _ctrThread;
	type = _type;
}

YaoDecodeThread::~YaoDecodeThread()
{
	if (decode != nullptr) {
		decode->close();
		delete decode;
		decode = nullptr;
	}
}

void YaoDecodeThread::run()
{
	int frameCount = 0;
	if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
		mediaCodec->init(*stream, JavaVMObj::surface);
	}
	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//���ƽ����벥���ٶ� todo
		/*if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
			if (ctrThread->getVideoFrameQueueSize() > 10) {
				continue;
			}
		}*/
		if (type == YaoDecoderType::YAODECODER_TYPE_AUDIO) {
			if (ctrThread->getAudioFrameQueueSize() > 20) {
				continue;
			}
		}


		YaoAVPacket* packet = nullptr;
		int ret = packetQueue.pop(&packet);
		if (ret) {
			continue;
		}

		//Ӳ����
		mediaCodec->send(packet);

		//�����
		decode->sendPacket(packet);
		while (1) {
			YaoAVFrame * frame = new YaoAVFrame();
			ret = decode->receiveFrame(frame);
			if (ret) {
				break;
			}

			//ͨ��ctrThread����� ��������frame����
			if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
				//todo �����
				//ctrThread->pushVideoFrameQueue(frame);
				//EyerLog("=========video frame push \n");
			}
			else if (type == YaoDecoderType::YAODECODER_TYPE_AUDIO) {
				ctrThread->pushAudioFrameQueue(frame);
				//EyerLog("+++++++++audio frame push \n");

			}

			frameCount++;
			//printf("frameCount:%d\n", frameCount);
		}
	
	}
}

int YaoDecodeThread::init(YaoAVStream* _stream)
{
	stream = _stream;
	return decode->init(stream);
}

int YaoDecodeThread::pushPacket(YaoAVPacket* packet)
{
	return packetQueue.push(packet);
}

int YaoDecodeThread::packetQueueSize()
{
	return packetQueue.queueSize();
}

int YaoDecodeThread::setMediaCodec(YaoMediaCodec * _mediaCodec){
	mediaCodec = _mediaCodec;
	return 0;
}