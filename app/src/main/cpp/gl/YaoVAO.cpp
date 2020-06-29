//
// Created by yaoyao on 20-6-23.
//
#include "YaoGL.h"
YaoVAO::YaoVAO()
{
    glGenVertexArrays(1, &vao);
    yaoGlTexture = new YaoGLTexture();
}

YaoVAO::~YaoVAO()
{
    for (int i = 0; i < vboList.size(); i++) {
        GLuint vbo = vboList[i];
        glDeleteBuffers(1, &vbo);
    }
    vboList.clear();

    if (ebo != NULL) {
        glDeleteBuffers(1, &ebo);
        ebo = NULL;
    }

    if (vao != NULL) {
        glDeleteVertexArrays(1, &vao);
        vao = NULL;
    }

    if (yaoGlTexture != nullptr) {
        delete yaoGlTexture;
        yaoGlTexture = NULL;
    }
}

int YaoVAO::addVertex3D(float * vertexs, int vertexCount, int layout)
{
    glBindVertexArray(vao);

    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertexs, GL_STATIC_DRAW);
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(layout);
    vboList.push_back(VBO);
    //vao½â°ó
    glBindVertexArray(0);

    return 0;
}

int YaoVAO::bindVAO()
{
    glBindVertexArray(vao);
    return 0;
}

int YaoVAO::setIndex(unsigned int * index, int _indexCount)
{
    glBindVertexArray(vao);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(unsigned int), index, GL_STATIC_DRAW);

    glBindVertexArray(0);
    indexCount = _indexCount;

    return 0;
}

int YaoVAO::bindTexture(char * imgPath)
{
    int ret = yaoGlTexture->loadImg(imgPath);
    if (ret) {
        return -1;
    }
    ret = yaoGlTexture->createTexImage2D();
    if (ret) {
        return -1;
    }
}

int YaoVAO::bindTextureWithData(unsigned char* _imgData)
{
    //yaoGlTexture->setImgData(_imgData);
    yaoGlTexture->imgData = _imgData;
    int ret = yaoGlTexture->createTexImage2D();
    if (ret) {
        return -1;
    }
}


int YaoVAO::draw()
{
    bindVAO();
    yaoGlTexture->bindTexture();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    return 0;
}
