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

int YaoMediaCodec::start()
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
    listGetMe = env->GetMethodID(ax_list_jclass, "start", "()V");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    env->CallVoidMethod(mediaCodec, listGetMe);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::start call fail \n");
    }*/
    return 0;
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
        EyerLog("cpp init NewGlobalRef mediaCodec is null\n");
    } else{
        EyerLog("cpp init NewGlobalRef mediaCodec is not null\n");

    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "init", "(IILandroid/view/Surface;)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }

    int ret = env->CallIntMethod(mediaCodec, listGetMe , avStream.getWidth(), avStream.getHeight(), surface);
    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::init call fail \n");
    }

    initStatus = 0;
    return ret;
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
    int ret = env->CallIntMethod(mediaCodec, listGetMe);

    initStatus = -1;

    return ret;
}

int YaoMediaCodec::send(int inputBufIndex, YaoAVPacket * annexbPkt)
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
    listGetMe = env->GetMethodID(ax_list_jclass, "send", "(I[B)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }

    jbyteArray jData = env->NewByteArray(annexbPkt->getSize());
    env->SetByteArrayRegion(jData, 0, annexbPkt->getSize(), (jbyte*)annexbPkt->getDataPtr());
    jlong time = (jlong)(annexbPkt->getSecPTS() * 1000);
    int ret = env->CallIntMethod(mediaCodec, listGetMe, inputBufIndex, jData);
//    if(env->ExceptionCheck()){
//        env->ExceptionDescribe();
//        env->ExceptionClear();
//        EyerLog("cpp YaoMediaCodec::send call fail \n");
//    }
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
    int ret = env->CallIntMethod(mediaCodec, listGetMe);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::recvAndRender call fail \n");
    }*/
    return ret;
}
int YaoMediaCodec::dequeueOutputBuffer(long long timeoutUs)
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
    listGetMe = env->GetMethodID(ax_list_jclass, "dequeueOutputBuffer", "(J)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    if(mediaCodec == nullptr){
        EyerLog("cpp mediaCodec is null\n");
    }
    int ret = env->CallIntMethod(mediaCodec, listGetMe, timeoutUs);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::dequeueOutputBuffer call fail \n");
    }*/
    return ret;
}

int YaoMediaCodec::dequeueInputBuffer(long long timeoutUs)
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
    listGetMe = env->GetMethodID(ax_list_jclass, "dequeueInputBuffer", "(J)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    if(mediaCodec == nullptr){
        EyerLog("cpp mediaCodec is null\n");
    }
    int ret = env->CallIntMethod(mediaCodec, listGetMe, timeoutUs);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::dequeueInputBuffer call fail \n");
    }*/
    return ret;
}

int YaoMediaCodec::queueInputBuffer(int inputBufIndex, int offset, int size, long long presentationTimeUs, int flags)
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
    listGetMe = env->GetMethodID(ax_list_jclass, "queueInputBuffer", "(IIIJI)V");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    if(mediaCodec == nullptr){
        EyerLog("cpp mediaCodec is null\n");
    }
    env->CallVoidMethod(mediaCodec, listGetMe, inputBufIndex, offset, size, presentationTimeUs, flags);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::queueInputBuffer call fail \n");
    }*/
    return 0;
}

long long YaoMediaCodec::getOutTime()
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
    long long ret = env->CallLongMethod(mediaCodec, listGetMe);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::getOutTime call fail \n");
    }*/
    return ret;
}

int YaoMediaCodec::renderFrame(int outIndex, bool isRender)
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
    listGetMe = env->GetMethodID(ax_list_jclass, "renderFrame", "(IZ)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    int ret = env->CallIntMethod(mediaCodec, listGetMe, outIndex, isRender);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::renderFrame call fail \n");
    }*/
    return ret;
}
int YaoMediaCodec::sendEndOfStream(int index)
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
    listGetMe = env->GetMethodID(ax_list_jclass, "sendEndOfStream", "(I)V");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    env->CallVoidMethod(mediaCodec, listGetMe, index);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::sendEndOfStream call fail \n");
    }*/
    return 0;
}

int YaoMediaCodec::flush()
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
    listGetMe = env->GetMethodID(ax_list_jclass, "flush", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    int ret = env->CallIntMethod(mediaCodec, listGetMe);
    /*if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        EyerLog("cpp YaoMediaCodec::flush call fail \n");
    }*/
    return ret;
}

int YaoMediaCodec::getInitStatus()
{
    return initStatus;
}

