//
// Created by yaoyao on 20-8-11.
//
#pragma once
#ifndef YAOPLAYERANDROID_JAVAVMOBJ_H
#define YAOPLAYERANDROID_JAVAVMOBJ_H
#include <jni.h>

class JavaVMObj{
public:
    static JavaVM * javaVm;
    static jobject jobj;
    static jobject mediaCodec;
    static jobject surface;
public:
    int callJavaMethod(jobject jobj, const char* funName, const char* sig);
    int callJavaMethod(jobject jobj, const char* funName, const char* sig, int dtime);
    int callJavaMethod(jobject jobj, const char* funName, const char* sig, int w, int h, jobject surface);
    int callJavaMethod(jobject jobj, const char* funName, const char* sig, jbyte data, long time);

};

#endif //YAOPLAYERANDROID_JAVAVMOBJ_H
