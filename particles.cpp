#include "particles.h"
#include <iostream>
Particles::Particles()
{
    initializeOpenGLFunctions();

    // Generate positions VBO
    arrayBuf.create();

    initParticles();

    color = QVector4D(0,1,0,1);
}

Particles::~Particles()
{
    arrayBuf.destroy();
}

void Particles::drawParticles(QOpenGLShaderProgram *program)
{
    glPointSize(5);
    arrayBuf.bind();

    program->setUniformValue("objectColor", color);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    //draw points
    glDrawArrays(GL_POINTS, 0, 3);
}

void Particles::initParticles()
{
    QVector3D vertices[] = {
        // Vertex data for face 0
        QVector3D(-0.3f, -0.3f,  1.6f),
        QVector3D( 0.3f, -0.3f,  1.3f),
        QVector3D(-0.3f,  0.3f,  1.3f)
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 3 * sizeof(QVector3D));
}
