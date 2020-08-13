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
    jclass cls = env->GetObjectClass(jobj);
    if(cls == NULL){
        EyerLog("~~~~~~~~~~cls is null \n");
    }

    jmethodID onCall = env->GetMethodID(cls, funName, sig);
    if(onCall == NULL){
        EyerLog("~~~~~~~~~~onCall is null \n");
    }
    return env->CallStaticIntMethod(cls, onCall);
}

int JavaVMObj::callJavaMethod(jobject jobj, const char* funName, const char* sig, int dtime)
{
    JNIEnv * env;
    JavaVMObj::javaVm->AttachCurrentThread(&env, NULL);
    jclass cls = env->GetObjectClass(jobj);
    if(cls == NULL){
        EyerLog("~~~~~~~~~~cls is null \n");
    }

    jmethodID onCall = env->GetMethodID(cls, funName, sig);
    if(onCall == NULL){
        EyerLog("~~~~~~~~~~onCall is null \n");
    }
    return env->CallIntMethod(cls, onCall, dtime);
}


