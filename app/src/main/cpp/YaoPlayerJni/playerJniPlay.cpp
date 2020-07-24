#include <jni.h>
#include <cpp/YaoPlayer/YaoPlayer.h>
#include "playerJniUtil.hpp"
#include "../YaoAV/YaoAV.h"
#include "../EyerCore/EyerLog.hpp"
#include "../YaoSL/YaoSL.h"


extern "C"
JNIEXPORT jlong JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1init(JNIEnv *env, jclass clazz, jstring path) {
    char * pathChar = jstringtochar(env, path);
    YaoPlayer * player = new YaoPlayer(pathChar);
    EyerLog("=============================player create cuccess \n");

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

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1gl_1drawFrame(JNIEnv *env, jclass clazz,
                                                                  jlong _player) {
    YaoPlayer * player = (YaoPlayer *)_player;
    return player->playerGl->drawFrame();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1gl_1surfaceChanged(JNIEnv *env, jclass clazz,
                                                                       jlong _player, jint width,
                                                                       jint height) {
    YaoPlayer * player = (YaoPlayer *)_player;
    return player->playerGl->surfaceChanged(width, height);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_player_Player_player_1print_1queue_1size(JNIEnv *env, jclass clazz,
                                                                       jlong _player) {
    YaoPlayer * player = (YaoPlayer *)_player;
    return player->printQueueSize();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_yao_yaoplayerandroid_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    std::string hello = "Hello from C++";
    YaoSL sl;
    //1 创建引擎
    sl.createEngin();

    //2 创建混音器
    sl.createMix();

    //3 配置音频信息
    sl.setDataSource(10);

    // 4 创建播放器
    sl.createAudioPlayer();

    return env->NewStringUTF(hello.c_str());
}
