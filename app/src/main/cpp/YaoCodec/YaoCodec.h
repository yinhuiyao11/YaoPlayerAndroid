//
// Created by Administrator on 2020/8/25.
//

#ifndef YAOPLAYERANDROID_YAOCODEC_H
#define YAOPLAYERANDROID_YAOCODEC_H

#include "../YaoAV/YaoAV.h"
#include <jni.h>

class YaoMediaCodec{
public:
    YaoMediaCodec();
    ~YaoMediaCodec();

    int init(YaoAVStream & avStream, jobject surface);
    int uninit();

    int send(int inputBufIndex, YaoAVPacket * annexbPkt);
    int recvAndRender();
    int dequeueOutputBuffer(long long timeoutUs);
    long long getOutTime();
    int renderFrame(int outindex, bool isRender);
    int dequeueInputBuffer(long long timeoutUs);
    int queueInputBuffer(int inputBufIndex, int offset, int size, long long presentationTimeUs, int flags);

    int sendEndOfStream(int index);
    int flush();
    int getInitStatus();

public:
    jobject mediaCodec = nullptr;
    int initStatus = -1;

};


#endif //YAOPLAYERANDROID_YAOCODEC_H
