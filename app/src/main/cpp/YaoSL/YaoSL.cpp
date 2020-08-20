//
// Created by Administrator on 2020/7/24.
//
#include <thread>
#include "YaoSL.h"
#include "../EyerCore/EyerLog.hpp"
#include "stdio.h"

//回调函数
void pcmCallBack(SLAndroidSimpleBufferQueueItf bf, void*contex)
{
    static unsigned char *buf = NULL;
    if (!buf){
        buf = new unsigned char[1024*1024];
    }

    YaoSL * sl = (YaoSL *)contex;
    YaoAVFrame* audioFrame = nullptr;
    //EyerLog("sl->playAudioFrameQueue->queueSize():%d\n", sl->playAudioFrameQueue->queueSize());

    while (sl->playAudioFrameQueue->queueSize() <= 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    sl->playAudioFrameQueue->pop(&audioFrame);
    EyerLog("audio frame Frame->getPts():%lld, weight:%d, heigt:%d\n", audioFrame->getPts(), audioFrame->getW(), audioFrame->getH());

    int len = audioFrame->getPerSampleSize() * audioFrame->getNBSamples() * audioFrame->getChannels();
    if (len > 0){//读取到数据 数据传入队列
        //声音停顿的话，check参数是否传对
        //声音音调不对的话，可能是pcm文件和pcm设置不对
        //audioFrame->getAudioData(buf);  音调不对，下面改成packed格式，音调对了，但还是有杂音
        audioFrame->getAudioPackedData(buf);

        (*bf)->Enqueue(bf,buf,len);
    }

}

YaoSL::YaoSL(YaoQueue<YaoAVFrame> * _playAudioFrameQueue)
{
    playAudioFrameQueue = _playAudioFrameQueue;

}

YaoSL::~YaoSL()
{
    //设置停止状态
    if (playerI) {
        (*playerI)->SetPlayState(playerI, SL_PLAYSTATE_STOPPED);
        playerI = 0;
    }
    //销毁播放器
    if (playerObject) {
        (*playerObject)->Destroy(playerObject);
        playerObject = 0;
        pcmQue = 0;
    }
    //销毁混音器
    if (mixObject) {
        (*mixObject)->Destroy(mixObject);
        mixObject = 0;
    }
    //销毁引擎
    if (engineObject) {
        (*engineObject)->Destroy(engineObject);
        engineObject = 0;
        engineI = 0;
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
    outMix = {SL_DATALOCATOR_OUTPUTMIX,mixObject};
    audioSink = {&outMix, 0};
    return 0;
}

int YaoSL::setDataSource(SLuint32 bufferNums, int sampleRate, int channels)
{
    //创建缓冲队列
    que = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,bufferNums};

    //音频格式配置（要和测试文件一致，实际使用中音频重采样成同样的格式）
    pcm = {
            SL_DATAFORMAT_PCM,
            (SLuint32)channels,//通道数
            (SLuint32)sampleRate * 1000,//采样率
            SL_PCMSAMPLEFORMAT_FIXED_32, // bitsPerSample
            SL_PCMSAMPLEFORMAT_FIXED_32,// containerSize
            SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,//声道
            SL_BYTEORDER_LITTLEENDIAN //字节序,小端
    };
    /*pcm = {
            SL_DATAFORMAT_PCM,
            2,//通道数
            SL_SAMPLINGRATE_48,//采样率
            SL_PCMSAMPLEFORMAT_FIXED_32, // bitsPerSample
            SL_PCMSAMPLEFORMAT_FIXED_32,// containerSize
            SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,//声道
            SL_BYTEORDER_LITTLEENDIAN //字节序,小端
    };*/

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




