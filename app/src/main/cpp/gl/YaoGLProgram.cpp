//
// Created by Administrator on 2020/6/23.
//
#include "YaoGL.h"
YaoGLProgram::YaoGLProgram(char* vertexShaderStr, char* fragmentShaderStr)
{
    program = glCreateProgram();
    YaoGLShader vertexShader(vertexShaderStr, YaoGLShaderType::YAOGL_SHADER_VERTEX);
    YaoGLShader fragmentShader(fragmentShaderStr, YaoGLShaderType::YAOGL_SHADER_FRAGMENT);

    glAttachShader(program, vertexShader.shader);
    glAttachShader(program, fragmentShader.shader);

    glLinkProgram(program);

    GLint logLen = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 1) {
        char* log = (char*)malloc(logLen);
        glGetProgramInfoLog(program, logLen, NULL, log);
        printf("program log:%s\n", log);
        free(log);
    }

}

int YaoGLProgram::useProgram()
{
    glUseProgram(program);
    return 0;
}

YaoGLProgram::~YaoGLProgram()
{
    if (program != 0) {
        glDeleteProgram(program);
        program = 0;
    }
}

int YaoGLProgram::setInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
    return 0;
}