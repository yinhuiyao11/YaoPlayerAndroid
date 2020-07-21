//
// Created by yaoyao on 20-7-19.
//

#include <string.h>
#include <android/log.h>
#include "../YaoGL/YaoGL.h"
#include "YaoPlayer.h"
#include "../EyerCore/EyerLog.hpp"

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
        "uniform sampler2D y;\n"
        "uniform sampler2D u;\n"
        "uniform sampler2D v;\n"
        "void main() {\n"
            "vec2 uv = vec2(TexCoord.x, TexCoord.y);\n"
            "vec3 yuv;\n"
            "vec3 rgb;\n"
            "yuv.x = texture(y, uv).r;\n"
            "yuv.y = texture(u, uv).r - 0.5;\n"
            "yuv.z = texture(v, uv).r - 0.5;\n"

            "rgb = mat3(1,1,1, 0,-0.39465,2.03211, 1.13983, -0.58060,0) * yuv;\n"
            "fragColor = vec4(rgb, 1.0);\n"
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
        1.0f,   0.0f, 0.0f,
        0.0f,  0.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
};

unsigned int index[] = {
        0,1,2,
        2,0,3
};

YaoPlayerGL::YaoPlayerGL(YaoQueue<YaoAVFrame> * playVideoFrameQueue)
{
    playVideoFrameQueueGL = playVideoFrameQueue;
}

YaoPlayerGL::~YaoPlayerGL(){

}

int YaoPlayerGL::surfaceChanged(int w, int h){
    program = new YaoGLProgram((char *)gl_vertexShader_source, (char *)gl_fragmentShader_source);
    vao = new YaoVAO();
    vao->addVertex3D(vVertex, 4, 0);
    vao->addVertex3D(vertexsUV, 4, 1);
    vao->setIndex(index, 6);

    //设置程序窗口
    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    return 0;
}

int YaoPlayerGL::drawFrame(){
    glClearColor(1.0, 0.0, 0.0, 1.0f);
    //清空颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    if(playVideoFrameQueueGL->queueSize() > 0){

        YaoAVFrame* videoFrame = nullptr;

        playVideoFrameQueueGL->pop(&videoFrame);
        EyerLog("video frame videoFrame->getPts():%lld, weight:%d, heigt:%d\n", videoFrame->getPts(), videoFrame->getW(), videoFrame->getH());

        int width = videoFrame->getW();
        int height = videoFrame->getH();

        unsigned char* y;
        unsigned char* u;
        unsigned char* v;

        y = (unsigned char*)malloc(width * height);
        u = (unsigned char*)malloc(width / 2 * height / 2);
        v = (unsigned char*)malloc(width / 2 * height / 2);

        videoFrame->getY(y);
        videoFrame->getU(u);
        videoFrame->getV(v);

        glActiveTexture(GL_TEXTURE0);
        program->redTexture->SetRedData(y, width,height);
        program->setInt("y", 0);

        glActiveTexture(GL_TEXTURE1);
        program->greenTexture->SetRedData(u, width / 2 , height / 2);
        program->setInt("u", 1);

        glActiveTexture(GL_TEXTURE2);
        program->blueTexture->SetRedData(v, width / 2 , height / 2);
        program->setInt("v", 2);


        /*
        vao->bindTextureWithData(y, width, height, 0);
        glActiveTexture(GL_TEXTURE0);
        vao->yaoGlTextures[0]->bindTexture();
        program->setInt("y", 0);


        vao->bindTextureWithData(u, width / 2 , height / 2, 1);
        glActiveTexture(GL_TEXTURE1);
        vao->yaoGlTextures[1]->bindTexture();
        program->setInt("u", 1);


        vao->bindTextureWithData(v, width / 2 , height / 2, 2);
        glActiveTexture(GL_TEXTURE2);
        vao->yaoGlTextures[2]->bindTexture();
        program->setInt("v", 2);

        */


        delete videoFrame;
        videoFrame = nullptr;

        free(y);
        free(u);
        free(v);
    }

    //设置为活动程序
    program->useProgram();
    checkGlError("glUseProgram");

    vao->draw();

    return 0;
}
