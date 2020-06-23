//
// Created by Administrator on 2020/6/23.
//

#ifndef YAOPLAYERANDROID_YAOGL_H
#define YAOPLAYERANDROID_YAOGL_H

#include "../../../../../../../NDK/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/GLES3/gl3.h"

class YaoGLProgram
{
public:
    YaoGLProgram(char* vertexShaderStr, char* fragmentShaderStr);
    ~YaoGLProgram();
    int useProgram();
    int setInt(const char* name, int value);
private:
    GLint program = 0;
};

#endif //YAOPLAYERANDROID_YAOGL_H
