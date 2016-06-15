#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Triangle : protected QOpenGLFunctions
{
public:
    Triangle();
    virtual ~Triangle();

    void drawTriangle(QOpenGLShaderProgram *program);

private:
    void initTriangle();

    QVector4D color;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // TRIANGLE_H
