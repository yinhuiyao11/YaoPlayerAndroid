#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include "gl/YaoGL.h"

#ifndef LOG_TAG
#define LOG_TAG "stone.stone"
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif

/*
#define STRINGIZE(x) #x
#define SHADER(shader) "" STRINGIZE(shader)
*/
/**
 * 顶点着色器源码
 */
auto gl_vertexShader_source =
        "#version 300 es\n"
        "layout(location = 0) in vec3 vPosition;\n"
        "out vec3 outPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(vPosition, 1.0);\n"
        "   outPos = vPosition;\n"
        "}\n";

/**
 * 片段着色器源码
 */
auto gl_fragmentShader_source =
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 fragColor;\n"
        "in vec3 outPos;\n"
        "void main() {\n"
        "   fragColor = vec4(outPos,1.0);\n"
        "}\n";

/**
 * 输出GL的属性值
 */
static void printGLString(const char *name, GLenum s) {
    const char *glName = reinterpret_cast<const char *>(glGetString(s));
    LOGE("GL %s = %s", name, glName);
}

static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("after %s() glError (0x%x)\n", op, error);
    }
}

/**
 * 着色器程序
 */
YaoGLProgram * program;
YaoVAO * vao;
/**
 * 顶点坐标
 */
float vVertex[] = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
};

unsigned int index[] = {
        0,1,2,
        2,3,0
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_yao_yaoplayerandroid_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yao_yaoplayerandroid_GLRender_surfaceChanged(JNIEnv *env, jobject thiz, jint w, jint h) {
    printGLString("Version", GL_VERSION);
    program = new YaoGLProgram((char *)gl_vertexShader_source, (char *)gl_fragmentShader_source);
    vao = new YaoVAO();
    vao->addVertex3D(vVertex, 4, 0);
    vao->setIndex(index, 6);

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