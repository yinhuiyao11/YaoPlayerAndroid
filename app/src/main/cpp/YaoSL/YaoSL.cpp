//
// Created by Administrator on 2020/7/24.
//
#include "YaoSL.h"
#include "../EyerCore/EyerLog.hpp"
#include "../../../../../../../NDK/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/SLES/OpenSLES.h"
#include "../../../../../../../NDK/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/SLES/OpenSLES_Android.h"
#include "stdio.h"

//回调函数
void pcmCallBack(SLAndroidSimpleBufferQueueItf bf, void*contex)
{
    //(*bf)->Enqueue(bf,buf,len);

    static FILE *fp = NULL;
    static  char *buf = NULL;
    if (!buf){
        buf = new char[1024*1024];
    }
    if (!fp){
        //没有声音 check这里
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/ads.mp4";
        fp = fopen("/storage/emulated/0/ST/test.pcm","rb");
    }
    if(!fp){
        EyerLog("fopen failed!");
        return;
    }

    if (feof(fp) == 0){

        int len = fread(buf,1,1024,fp);
        if (len > 0){//读取到数据 数据传入队列
            //声音停顿的话，check参数是否传对
            //声音音调不对的话，可能是pcm文件和pcm设置不对
            (*bf)->Enqueue(bf,buf,len);

        }

    }
}

int YaoSL::createEngin()
{
    //a 创建引擎对象
    SLresult re;
    re = slCreateEngine(&engineObject,0,0,0,0,0);
    if (re != SL_RESULT_SUCCESS){
        EyerLog("slCreateEngine fail \n");
        return -1;
    }

    //b 实例化 SL_BOOLEAN_FALSE等待对象创建
    re = (*engineObject)->Realize(engineObject,SL_BOOLEAN_FALSE);
    if (re != SL_RESULT_SUCCESS){
        EyerLog("engineObject Realize fail \n");
        return -1;
    }

    //c 获取接口
    re = (*engineObject)->GetInterface(engineObject,SL_IID_ENGINE,&engineI);
    if (re != SL_RESULT_SUCCESS){
        EyerLog("engineI GetInterface fail \n");
        return -1;
    }

    return 0;
}

//创建混音器
int YaoSL::createMix()
{
    //a 输出混音器
    SLresult re;
    re = (*engineI)->CreateOutputMix(engineI, &mixObject, 0, 0, 0);
    if(re != SL_RESULT_SUCCESS){
        EyerLog("CreateOutputMix fail \n");
        return -1;
    }

    //b 实例化
    re = (*mixObject)->Realize(mixObject, SL_BOOLEAN_FALSE);
    if(re != SL_RESULT_SUCCESS){
        EyerLog("mixObject Realize fail \n");
        return -1;
    }

    //c 输出
    SLDataLocator_OutputMix outMix = {SL_DATALOCATOR_OUTPUTMIX,mixObject};
    audioSink = {&outMix, 0};
    return 0;
}

int YaoSL::setDataSource(SLuint32 bufferNums)
{
    //创建缓冲队列
    SLDataLocator_AndroidSimpleBufferQueue que = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,bufferNums};

    //音频格式配置（要和测试文件一致，实际使用中音频重采样成同样的格式）
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            2,//通道数
            SL_SAMPLINGRATE_44_1,//采样率
            SL_PCMSAMPLEFORMAT_FIXED_16, // bitsPerSample
            SL_PCMSAMPLEFORMAT_FIXED_16,// containerSize
            SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,//声道
            SL_BYTEORDER_LITTLEENDIAN //字节序,小端
    };
    //播放器使用的结构体
    dataSource = {&que,&pcm};
    return 0;
}

/*void YaoSL::pcmCallBack(SLAndroidSimpleBufferQueueItf bf, void * contex)
{
    //(*bf)->Enqueue(bf,buf,len);
}*/

int YaoSL::createAudioPlayer()
{
    SLresult re;
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};//接口id
    const SLboolean  req[] = {SL_BOOLEAN_TRUE};//接口开放
    //sizeof(ids)/sizeof(SLInterfaceID) 参数个数
    re = (*engineI)->CreateAudioPlayer(engineI,&playerObject,&dataSource,&audioSink, sizeof(ids)/sizeof(SLInterfaceID),ids,req);
    if(engineI == NULL){
        EyerLog("engineI is null\n");
    }
    if(playerObject == NULL){
        EyerLog("playerObject is null\n");
    }
    if(dataSource.pLocator == nullptr){
        EyerLog("dataSource is null\n");
    }
    if(dataSource.pFormat == nullptr){
        EyerLog("dataSource.pFormat is null\n");
    }
    if(audioSink.pLocator == nullptr){
        EyerLog("audioSink is null\n");
    }
    if(audioSink.pFormat == nullptr){
        EyerLog("audioSink.pFormat is null\n");
    }

    EyerLog("sizeof(ids)/sizeof(SLInterfaceID) : %d\n", sizeof(ids)/sizeof(SLInterfaceID));

    if (re != SL_RESULT_SUCCESS) {
        EyerLog("CreateAudioPlayer  failed!, re:%d", re);
    }

    //实例化
    (*playerObject)->Realize(playerObject,SL_BOOLEAN_FALSE);
    //获取接口
    re = (*playerObject)->GetInterface(playerObject,SL_IID_PLAY,&playerI);
    if (re != SL_RESULT_SUCCESS)
    {
        EyerLog("player GetInterface  failed!");
    }
    //获取缓冲队列接口
    re =(*playerObject)->GetInterface(playerObject,SL_IID_BUFFERQUEUE,&pcmQue);
    if (re != SL_RESULT_SUCCESS)
    {
        EyerLog("player GetInterface BUFFERQUEUE failed!");
    }

    //设置回调函数,播放队列为空的时候调用
    /*
     * 第二个参数是回调函数 第三个参数是 给回调函数传的参数
     */
    (*pcmQue)->RegisterCallback(pcmQue,pcmCallBack,this);
    //设置状态 播放
    (*playerI)->SetPlayState(playerI,SL_PLAYSTATE_PLAYING);

    //启动队列回调
    (*pcmQue)->Enqueue(pcmQue,"",1);

    return 0;
}

int YaoSL::setPcmQueData()
{
    return 0;
}




