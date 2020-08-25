//
// Created by Administrator on 2020/8/25.
//

#ifndef YAOPLAYERANDROID_YAOCODEC_H
#define YAOPLAYERANDROID_YAOCODEC_H

#include "../YaoAV/YaoAV.h"
#include "../../../../../../../NDK/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/jni.h"
#include <jni.h>

class YaoMediaCodec{
public:
    YaoMediaCodec();
    ~YaoMediaCodec();

    int init(YaoAVReader & avReader, jobject surface);
    int uninit();

    int send(YaoAVPacket * annexbPkt);
    int recvAndRender();
    int dequeueOutputBuffer();
    long getOutTime();
    int renderFrame(int outIndex);

private:
    jobject eyerMediaCodec = nullptr;
};


#endif //YAOPLAYERANDROID_YAOCODEC_H
