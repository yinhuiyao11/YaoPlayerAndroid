#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include "gl/YaoGL.h"
#include "YaoAV/YaoAV.h"

#ifndef LOG_TAG
#define LOG_TAG "stone.stone"
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavfilter/avfilter.h"
#include "libswscale/swscale.h"
}
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
        "layout(location = 1) in vec3 aTexCoord;\n"
        "out vec3 TexCoord;\n"
        "out vec3 outPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(vPosition, 1.0);\n"
        "   outPos = vPosition;\n"
        "   TexCoord = aTexCoord;\n"
        "}\n";

/**
 * 片段着色器源码
 */
auto gl_fragmentShader_source =
    "#version 300 es\n"
    "precision mediump float;\n"
    "out vec4 fragColor;\n"
    "in vec3 outPos;\n"
    "in vec3 TexCoord;\n"
    "uniform sampler2D t;\n"
    "void main() {\n"
    "vec2 uv = vec2(TexCoord.x, TexCoord.y);\n"
    "   fragColor = texture(t, uv);\n"
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

//纹理坐标
float vertexsUV[] = {
        1.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        0.0f,  0.0f, 0.0f,
        1.0f,   0.0f, 0.0f,
};

unsigned int index[] = {
        0,1,2,
        2,0,3
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_yao_yaoplayerandroid_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    //std::string hello = "Hello from C++";
    std::string hello = avcodec_configuration();
    return env->NewStringUTF(hello.c_str());
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

extern "C"
JNIEXPORT jlong JNICALL
Java_com_yao_yaoplayerandroid_av_AVReader_avreader_1init(JNIEnv *env, jclass clazz, jstring url) {
    // TODO: implement avreader_init()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_av_AVReader_avreader_1uninit(JNIEnv *env, jclass clazz,
                                                           jlong avreader) {
    // TODO: implement avreader_uninit()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_av_AVReader_avreader_1open(JNIEnv *env, jclass clazz, jlong avreader,
                                                         jstring url) {
    // TODO: implement avreader_open()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_av_AVReader_avreader_1close(JNIEnv *env, jclass clazz,
                                                          jlong avreader) {
    // TODO: implement avreader_close()
}extern "C"
JNIEXPORT jint JNICALL
Java_com_yao_yaoplayerandroid_av_AVReader_avreader_1print_1info(JNIEnv *env, jclass clazz,
                                                                jlong avreader) {
    // TODO: implement avreader_print_info()
}