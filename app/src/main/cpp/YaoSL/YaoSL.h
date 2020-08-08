//
// Created by Administrator on 2020/7/22.
//

#ifndef YAOPLAYERANDROID_YAOSL_H
#define YAOPLAYERANDROID_YAOSL_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "YaoAV/YaoAV.h"
#include "YaoQueue/Queue.h"

class YaoSL{
public:
    YaoSL(YaoQueue<YaoAVFrame> * playAudioFrameQueue);
    ~YaoSL();
    int createEngin();
    int createMix();
    int setDataSource(SLuint32 bufferNums);
    int createAudioPlayer();

    int setPcmQueData();
    //void pcmCallBack(SLAndroidSimpleBufferQueueItf bf, void*contex);

public:
    YaoQueue<YaoAVFrame> * playAudioFrameQueue = nullptr;

private:
    SLObjectItf engineObject = NULL;
    SLEngineItf engineI = NULL;

    SLObjectItf mixObject = NULL;
    SLDataLocator_OutputMix outMix = {};
    SLDataSink audioSink = {};

    SLDataLocator_AndroidSimpleBufferQueue que = {};
    SLDataFormat_PCM pcm = {};
    SLDataSource dataSource = {};

    SLObjectItf playerObject = NULL;
    SLPlayItf playerI = NULL;
    SLAndroidSimpleBufferQueueItf pcmQue = NULL;

};
#endif //YAOPLAYERANDROID_YAOSL_H
