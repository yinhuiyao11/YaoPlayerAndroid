//
// Created by Administrator on 2020/7/22.
//

#ifndef YAOPLAYERANDROID_YAOSL_H
#define YAOPLAYERANDROID_YAOSL_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class YaoSL{
public:
    int createEngin();
    int createMix();
    int setDataSource(SLuint32 bufferNums);
    int createAudioPlayer();

    int setPcmQueData();
    //void pcmCallBack(SLAndroidSimpleBufferQueueItf bf, void*contex);
private:
    SLObjectItf engineObject = NULL;
    SLEngineItf engineI = NULL;

    SLObjectItf mixObject = NULL;
    SLDataSink audioSink = {};
    SLDataSource dataSource = {};

    SLObjectItf playerObject = NULL;
    SLPlayItf playerI = NULL;
    SLAndroidSimpleBufferQueueItf pcmQue = NULL;


};
#endif //YAOPLAYERANDROID_YAOSL_H
