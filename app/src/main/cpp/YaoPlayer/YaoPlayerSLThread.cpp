//
// Created by Administrator on 2020/7/29.
//
#include "../EyerCore/EyerLog.hpp"
#include "YaoPlayer.h"
#include "../YaoAV/YaoAV.h"
#include "../YaoQueue/Queue.h"

YaoPlayerSLThread::YaoPlayerSLThread(YaoQueue<YaoAVFrame> * _playAudioFrameQueue)
{
    playAudioFrameQueue = _playAudioFrameQueue;
}

YaoPlayerSLThread::~YaoPlayerSLThread()
{

}

void YaoPlayerSLThread::run()
{
    EyerLog("`````````````YaoPlayerSLThread::run playAudioFrameQueue:%d\n", playAudioFrameQueue->queueSize());
    YaoSL playerSl(playAudioFrameQueue);
    //1 创建引擎
    playerSl.createEngin();
    //2 创建混音器
    playerSl.createMix();
    //3 配置音频信息
    playerSl.setDataSource(10);
    // 4 创建播放器
    playerSl.createAudioPlayer();
}