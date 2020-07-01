//
// Created by Administrator on 2020/7/1.
//

#include <string>
#include "../../../../../../../NDK/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/jni.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_yao_yaoplayerandroid_AVReader_avreader_1init(JNIEnv *env, jclass clazz, jstring url) {
    // TODO: implement avreader_init()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_AVReader_avreader_1uninit(JNIEnv *env, jclass clazz, jlong avreader) {
    // TODO: implement avreader_uninit()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_AVReader_avreader_1open(JNIEnv *env, jclass clazz, jlong avreader) {
    // TODO: implement avreader_open()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_AVReader_avreader_1close(JNIEnv *env, jclass clazz, jlong avreader) {
    // TODO: implement avreader_close()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_AVReader_avreader_1print_1info(JNIEnv *env, jclass clazz,
                                                             jlong avreader) {
    // TODO: implement avreader_print_info()
}