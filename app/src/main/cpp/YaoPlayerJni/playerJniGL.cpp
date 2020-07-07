/*
#include <jni.h>
#include <string>
#include <android/log.h>
#include "YaoGL/YaoGL.h"

#ifndef LOG_TAG
#define LOG_TAG "stone.stone"
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif

*/
/**
 * 输出GL的属性值
 *//*

static void printGLString(const char *name, GLenum s) {
    const char *glName = reinterpret_cast<const char *>(glGetString(s));
    LOGE("GL %s = %s", name, glName);
}

static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("after %s() glError (0x%x)\n", op, error);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yao_yaoplayerandroid_GLRender_surfaceChanged(JNIEnv *env, jobject thiz, jint w, jint h) {
printGLString("Version", GL_VERSION);
program = new YaoGLProgram((char *)gl_vertexShader_source, (char *)gl_fragmentShader_source);
vao = new YaoVAO();
vao->addVertex3D(vVertex, 4, 0);
vao->addVertex3D(vertexsUV, 4, 1);
vao->setIndex(index, 6);
unsigned char imgData[] ={
        255,0,0,  0,255,0,
        0,0,255,  127,127,127
};
vao->bindTextureWithData(imgData, 2, 2);

//设置程序窗口
glViewport(0, 0, w, h);
checkGlError("glViewport");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yao_yaoplayerandroid_GLRender_drawFrame(JNIEnv *env, jobject thiz) {

glClearColor(1.0, 1.0, 1.0, 1.0f);
//清空颜色缓冲区
glClear(GL_COLOR_BUFFER_BIT);

//设置为活动程序
program->useProgram();
checkGlError("glUseProgram");

vao->draw();

}
*/
