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

    int send(YaoAVPacket * annexbPkt);
    int recvAndRender();
    int dequeueOutputBuffer();
    long getOutTime();
    int renderFrame(int outIndex);

public:
    static jobject eyerMediaCodec = nullptr;
    static jobject yaoMediaCodec = nullptr;

};


#endif //YAOPLAYERANDROID_YAOCODEC_H
