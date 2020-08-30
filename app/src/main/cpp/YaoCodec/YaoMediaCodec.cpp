//
// Created by Administrator on 2020/8/25.
//
#include "YaoCodec.h"
#include "../YaoPlayerJni/JavaVMObj.h"
#include "../EyerCore/EyerLog.hpp"

YaoMediaCodec::YaoMediaCodec()
{

}
YaoMediaCodec::~YaoMediaCodec()
{

}

int YaoMediaCodec::init(YaoAVStream & avStream, jobject surface)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);

    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }

    jmethodID mediaCodecMethod = env->GetMethodID(ax_list_jclass, "<init>", "()V");
    if(mediaCodecMethod == NULL){
        EyerLog("mediaCodecMethod is null \n");
    }

    jobject _mediaCodec = env->NewObject(ax_list_jclass, mediaCodecMethod);
    if(_mediaCodec == NULL){
        EyerLog("_mediaCodec is null \n");
    }

    mediaCodec = env->NewGlobalRef(_mediaCodec);
    if(mediaCodec == nullptr){
        EyerLog("cpp init mediaCodec is null\n");
    } else{
        //EyerLog("cpp init mediaCodec is not null\n");

    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "init", "(IILandroid/view/Surface;)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }

    int findObj = env->CallIntMethod(mediaCodec, listGetMe , avStream.getWidth(), avStream.getHeight(), surface);

    return 0;
}

int YaoMediaCodec::uninit()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "uninit", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    int findObj = env->CallIntMethod(mediaCodec, listGetMe);
    return 0;
}

int YaoMediaCodec::send(YaoAVPacket * annexbPkt)
{
    if(mediaCodec == nullptr){
        EyerLog("cpp send mediaCodec is null\n");
    } else{
        //EyerLog("cpp send mediaCodec is not null\n");

    }
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }

    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "send", "([BJ)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }

    jbyteArray jData = env->NewByteArray(annexbPkt->getSize());
    env->SetByteArrayRegion(jData, 0, annexbPkt->getSize(), (jbyte*)annexbPkt->getDataPtr());
    jlong time = (jlong)(annexbPkt->getSecPTS() * 1000);
    int ret = env->CallIntMethod(mediaCodec, listGetMe, jData, time);

    return ret;
}
int YaoMediaCodec::recvAndRender()
{
    if(mediaCodec == nullptr){
        EyerLog("cpp recvAndRender mediaCodec is null\n");
    } else{
        //EyerLog("cpp recvAndRender mediaCodec is not null\n");

    }
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "recvAndRender", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    int findObj = env->CallIntMethod(mediaCodec, listGetMe);
    return 0;
}
int YaoMediaCodec::dequeueOutputBuffer()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }

    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "dequeueOutputBuffer", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    if(mediaCodec == nullptr){
        EyerLog("cpp mediaCodec is null\n");
    }
    int findObj = env->CallIntMethod(mediaCodec, listGetMe);

    return 0;
}
long YaoMediaCodec::getOutTime()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "getOutTime", "()J");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    int findObj = env->CallLongMethod(mediaCodec, listGetMe);
    return 0;
}
int YaoMediaCodec::renderFrame(int outIndex)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::mediaCodec);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }

    // 获取方法 
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "renderFrame", "(I)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    int findObj = env->CallIntMethod(mediaCodec, listGetMe, outIndex);

    return 0;
}