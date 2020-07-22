#include "YaoGL.h"
//#include "YaoImg/stb_image.h"

YaoGLTexture::YaoGLTexture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //设置一字节对齐
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

YaoGLTexture::~YaoGLTexture()
{

}
int YaoGLTexture::loadImg(char* imgPath)
{
    /*stbi_set_flip_vertically_on_load(true);
    imgData = stbi_load(imgPath, &width, &height, &nrChannels, 0);
    printf("width %d, height %d, nrChannels %d \n", width, height, nrChannels);
    if (width <= 0 && height <= 0) {
        return -1;
    }*/
    return 0;
}

int YaoGLTexture::setRedData(unsigned char * data, int width, int height)
{
    //操作texture前，先bind
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);

    return 0;
}

int YaoGLTexture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    return 0;
}

