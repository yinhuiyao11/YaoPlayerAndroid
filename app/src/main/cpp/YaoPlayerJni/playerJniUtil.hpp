#ifndef	PLAYER_JNI_UTIL_H
#define	PLAYER_JNI_UTIL_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

char * jstringtochar(JNIEnv *env, jstring jstr);

#ifdef __cplusplus
}
#endif

#endif