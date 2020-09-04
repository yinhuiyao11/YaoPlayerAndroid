#include <cpp/YaoPlayerJni/JavaVMObj.h>
#include <cpp/YaoCodec/YaoCodec.h>
#include <unistd.h>
#include "YaoPlayer.h"
#include "EyerCore/EyerLog.hpp"
#include "../YaoAV/EyerAVBitstreamFilter.hpp"

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
    Eyer::EyerAVBitstreamFilter bitstreamFilter(Eyer::EyerAVBitstreamFilterType::h264_mp4toannexb, *stream);
    if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
        mediaCodec->init(*stream, JavaVMObj::surface);
        EyerLog("run mediaCodec->init\n");
    }
	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//控制解码与播放速度 todo
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

        int inputBufferIndex = -1;
        if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
            inputBufferIndex = mediaCodec->dequeueInputBuffer(1000 * 100);

            if(inputBufferIndex < 0){
                continue;
            }
        }

        EyerLog("Input Index: %d\n", inputBufferIndex);

        YaoAVPacket *packet = nullptr;
        int ret = packetQueue.pop(&packet);
        if (ret) {
            continue;
        }

        if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
            bitstreamFilter.SendPacket(packet);
            //硬解码
            while (!stopFlag) {
                YaoAVPacket changedPacket;
                int ret = bitstreamFilter.ReceivePacket(&changedPacket);
                if(ret){
                    break;
                }

                /*for (int i = 0; i < 4; i++) {
                    EyerLog("~~~~~changedPacket data%d: %d \n", i, changedPacket.getDataPtr()[i]);
                }*/


                if(inputBufferIndex >= 0){
                    ret = mediaCodec->send(inputBufferIndex, &changedPacket);
                    stream->scalePacketPts(changedPacket);
                    EyerLog("pts:%lld \n", (long long)(changedPacket.getSecPTS() * 1000.0));
                    mediaCodec->queueInputBuffer(inputBufferIndex, 0, changedPacket.getSize(), (long long)(changedPacket.getSecPTS() * 1000.0), 0);
                    inputBufferIndex = -1;
                }

                frameCount++;


            }
        }

		//软解码
        if (type == YaoDecoderType::YAODECODER_TYPE_AUDIO) {
            decode->sendPacket(packet);
            while (1) {
                YaoAVFrame *frame = new YaoAVFrame();
                ret = decode->receiveFrame(frame);
                if (ret) {
                    break;
                }

                //通过ctrThread句柄， 向其塞入frame数据
                /*if (type == YaoDecoderType::YAODECODER_TYPE_VIDEO) {
                    //todo 软解码
                    //ctrThread->pushVideoFrameQueue(frame);
                    //EyerLog("=========video frame push \n");
                }*/
                //else if (type == YaoDecoderType::YAODECODER_TYPE_AUDIO) {
                ctrThread->pushAudioFrameQueue(frame);
                //EyerLog("+++++++++audio frame push \n");

                //}

                frameCount++;
                //printf("frameCount:%d\n", frameCount);
            }
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