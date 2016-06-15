#ifndef PARTICLES_H
#define PARTICLES_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Particles : protected QOpenGLFunctions
{
public:
    Particles();
    virtual ~Particles();

    void drawParticles(QOpenGLShaderProgram *program);

private:
    void initParticles();

    QVector4D color;

    QOpenGLBuffer arrayBuf;
};

#endif // PARTICLES_H
