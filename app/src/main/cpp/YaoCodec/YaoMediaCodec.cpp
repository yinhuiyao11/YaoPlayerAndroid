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

    int ret = env->CallIntMethod(mediaCodec, listGetMe , avStream.getWidth(), avStream.getHeight(), surface);

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
    int ret = env->CallLongMethod(mediaCodec, listGetMe);
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
    return ret;
}