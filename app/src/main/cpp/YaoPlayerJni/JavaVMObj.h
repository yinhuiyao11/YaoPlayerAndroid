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
public:
    //int callJavaStaticMethod(const char* className, const char* funName, const char* sig);
    int callJavaStaticMethod(jobject jobj, const char* funName, const char* sig);
};

#endif //YAOPLAYERANDROID_JAVAVMOBJ_H
