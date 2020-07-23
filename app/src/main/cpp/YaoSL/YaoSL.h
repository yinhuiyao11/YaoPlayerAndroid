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
    int setDataSource();
    int createAudioPlayer();

    int setPcmQueData();
private:
    SLObjectItf engineObject = NULL;
    SLEngineItf engineSL = NULL;

    SLObjectItf playerObject = NULL;

    SLDataSource dataSource = {};

    SLObjectItf player = NULL;
    SLPlayItf playerInterface = NULL;
    SLAndroidSimpleBufferQueueItf pcmQue = NULL;


};
#endif //YAOPLAYERANDROID_YAOSL_H
