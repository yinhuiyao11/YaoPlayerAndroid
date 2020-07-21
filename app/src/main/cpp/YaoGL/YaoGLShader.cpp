//
// Created by yaoyao on 20-6-23.
//

#include "YaoGL.h"

YaoGLShader::YaoGLShader(char* shaderStr, YaoGLShaderType type)
{
    if (type == YaoGLShaderType::YAOGL_SHADER_VERTEX) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == YaoGLShaderType::YAOGL_SHADER_FRAGMENT) {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    else {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    glShaderSource(shader, 1, &shaderStr, NULL);
    glCompileShader(shader);

    GLint logLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 1) {
        char* log = (char*)malloc(logLen);
        glGetShaderInfoLog(shader, logLen, NULL, log);
        printf("shader compile error:%s \n", log);
        free(log);
    }

}

YaoGLShader::~YaoGLShader()
{
    if (shader != 0) {
        glDeleteShader(shader);
        shader = 0;
    }
}
