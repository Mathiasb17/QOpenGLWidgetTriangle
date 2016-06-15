#include "triangle.h"

#include <iostream>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

Triangle::Triangle():
    indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initTriangle();

    color = QVector4D(1,0,0,1);
}

Triangle::~Triangle()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Triangle::initTriangle()
{
    QVector3D vertices[] = {
        // Vertex data for face 0
        QVector3D(-1.0f, -1.0f,  1.0f),
        QVector3D( 1.0f, -1.0f,  1.0f),
        QVector3D(-1.0f,  1.0f,  1.0f)
    };

    GLushort indices[] = {
         0,  1,  2,
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 3 * sizeof(QVector3D));

    indexBuf.bind();
    indexBuf.allocate(indices, 3 * sizeof(GLushort));
}

void Triangle::drawTriangle(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    program->setUniformValue("objectColor", color);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, 0);
}


