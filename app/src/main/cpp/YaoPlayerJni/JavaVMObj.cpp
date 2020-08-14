//
// Created by yaoyao on 20-8-11.
//
#include "JavaVMObj.h"
#include "../EyerCore/EyerLog.hpp"

JavaVM * JavaVMObj::javaVm = nullptr;
jobject JavaVMObj::jobj = NULL;

int JavaVMObj::callJavaMethod(jobject jobj, const char* funName, const char* sig)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("~~~~~~~~~~jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, funName, sig);
    if(listGetMe == NULL){
        EyerLog("~~~~~~~~~~jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe);
    return 0;
}

int JavaVMObj::callJavaMethod(jobject jobj, const char* funName, const char* sig, int dtime)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    // 获取类
    jclass ax_list_jclass = env->GetObjectClass(JavaVMObj::jobj);
    if(ax_list_jclass == NULL){
        EyerLog("~~~~~~~~~~jclass is null \n");
    }
    // 获取方法
    jmethodID listGetMe;
    listGetMe = env->GetMethodID(ax_list_jclass, funName, sig);
    if(listGetMe == NULL){
        EyerLog("~~~~~~~~~~jni jmethodID is null \n");
    }
    jobject findObj = env->CallObjectMethod(JavaVMObj::jobj, listGetMe , dtime);
    EyerLog("~~~~~~~~~~playSetProgressBar called in cpp \n");
    return 0;
}


