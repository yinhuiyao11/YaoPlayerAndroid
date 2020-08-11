//
// Created by yaoyao on 20-8-11.
//
#include "JavaVMObj.h"
#include "../EyerCore/EyerLog.hpp"

JavaVM * JavaVMObj::javaVm = nullptr;

//int JavaVMObj::callJavaStaticMethod(const char* className, const char* funName, const char* sig)
int JavaVMObj::callJavaStaticMethod()
{
    JNIEnv *env1 = NULL;
    JavaVMObj::javaVm->AttachCurrentThread(&env1, NULL);

    jclass clazz1 = env1->FindClass("com/yao/yaoplayerandroid/player/PlayEndCallback");
    if(clazz1 == NULL){
        EyerLog("~~~~~~~~~~clazz is null \n");
    }
    jmethodID onCall = env1->GetStaticMethodID(clazz1, "onEndCallBack","()I");
    if(onCall == NULL){
        EyerLog("~~~~~~~~~~onCall is null \n");
    } else{
        EyerLog("~~~~~~~~~~onCall is not null \n");

    }
    env1->CallStaticIntMethod(clazz1, onCall);
    /*JNIEnv *env = NULL;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);

    //jclass clazz = env->FindClass("com/yao/yaoplayerandroid/player/PlayEndCallback");
    jclass clazz = env->FindClass(className);
    if(clazz == NULL){
        EyerLog("~~~~~~~~~~clazz is null \n");
    }
    //jmethodID onCall = env->GetStaticMethodID(clazz, "onEndCallBack","()I");
    jmethodID onCall = env->GetStaticMethodID(clazz, funName,sig);
    if(onCall == NULL){
        EyerLog("~~~~~~~~~~onCall is null \n");
    } else{
        EyerLog("~~~~~~~~~~onCall is not null \n");
    }
    env->CallStaticIntMethod(clazz, onCall);*/
}

