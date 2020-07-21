//
// Created by Administrator on 2020/6/23.
//

#ifndef YAOPLAYERANDROID_YAOGL_H
#define YAOPLAYERANDROID_YAOGL_H

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

#ifndef LOG_TAG
#define LOG_TAG "stone.stone"
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif
enum YaoGLShaderType
{
    YAOGL_SHADER_VERTEX = 1,
    YAOGL_SHADER_FRAGMENT = 2
};

class YaoGLTexture {
public:
    YaoGLTexture();
    ~YaoGLTexture();
    int loadImg(char* imgPath);
    int createTexImage2D();
    int bindTexture();
    int setImgData(unsigned char* _imgData);

    int SetRedData(unsigned char * data, int width, int height);

public:
    unsigned char* imgData = nullptr;
    int width = 0;
    int height = 0;

private:
    GLuint texture = 0;
    int nrChannels = 0;
};

class YaoGLShader
{
public:
    YaoGLShader(char * shaderStr, YaoGLShaderType type);
    ~YaoGLShader();
public:
    GLuint shader = 0;
};

class YaoGLProgram
{
public:
    YaoGLProgram(char* vertexShaderStr, char* fragmentShaderStr);
    ~YaoGLProgram();
    int useProgram();
    int setInt(const char* name, int value);
private:
    GLuint program = 0;
public:
    YaoGLTexture * redTexture = nullptr;
    YaoGLTexture * greenTexture = nullptr;
    YaoGLTexture * blueTexture = nullptr;
};

class YaoVAO
{
public:
    YaoVAO();
    ~YaoVAO();
    int addVertex3D(float* vertexs, int vertexCount, int layout);
    int bindVAO();
    int setIndex(unsigned int * index, int indexCount);
    int bindTexture(char * imgPath);
    int bindTextureWithData(unsigned char* imgData, int _width, int _height, int texture_num);
    int draw();

    std::vector<YaoGLTexture *> yaoGlTextures;

private:
    GLuint vao = 0;
    GLuint ebo = 0;
    std::vector<GLuint> vboList;
    int indexCount = 0;
};

#endif //YAOPLAYERANDROID_YAOGL_H
