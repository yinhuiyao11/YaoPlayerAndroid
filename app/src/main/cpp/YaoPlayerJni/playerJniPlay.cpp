#include <jni.h>
#include <cpp/YaoPlayer/YaoPlayer.h>
#include "playerJniUtil.hpp"
#include "../YaoAV/YaoAV.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1init(JNIEnv *env, jclass clazz, jstring path) {
    char * pathChar = jstringtochar(env, path);
    YaoPlayer * player = new YaoPlayer(pathChar);
    return (jlong)player;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1uninit(JNIEnv *env, jclass clazz,
                                                           jlong avreader) {
    YaoPlayer * player = (YaoPlayer *)avreader;
    delete player;
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1open(JNIEnv *env, jclass clazz, jlong avreader,
                                                         jdouble time) {
    YaoPlayer * player = (YaoPlayer *)avreader;
    return player->open(time);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1play(JNIEnv *env, jclass clazz,
                                                         jlong avreader) {
    YaoPlayer * player = (YaoPlayer *)avreader;
    return player->play();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1stop(JNIEnv *env, jclass clazz,
                                                         jlong avreader) {
    YaoPlayer * player = (YaoPlayer *)avreader;
    return player->stop();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1pause(JNIEnv *env, jclass clazz,
                                                          jlong avreader) {
    YaoPlayer * player = (YaoPlayer *)avreader;
    return player->pause();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1seek(JNIEnv *env, jclass clazz, jlong avreader,
                                                         jdouble time) {
    YaoPlayer * player = (YaoPlayer *)avreader;
    return player->seek(time);
}