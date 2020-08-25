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

int YaoMediaCodec::init(YaoAVReader & avReader, jobject surface)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "init", "(IILjava/lang/Class;)I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe , avReader.getVideoWidth(), avReader.getVideoHeight(), surface);
    return 0;
}

int YaoMediaCodec::uninit()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "uninit", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}

int YaoMediaCodec::send(YaoAVPacket * annexbPkt)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "uninit", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}
int YaoMediaCodec::recvAndRender()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "uninit", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}
int YaoMediaCodec::dequeueOutputBuffer()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "dequeueOutputBuffer", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}
long YaoMediaCodec::getOutTime()
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "getOutTime", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}
int YaoMediaCodec::renderFrame(int outIndex)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, "renderFrame", "()I");
    if(listGetMe == NULL){
        EyerLog("jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}