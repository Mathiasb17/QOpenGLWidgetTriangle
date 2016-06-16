#include "gldisplay.h"

#include <iostream>
#include <cmath>

#include <QMouseEvent>

GLDisplay::GLDisplay(QWidget *parent):
    QOpenGLWidget(parent),
    m_geometry(0),
    m_particles(0)
{
    matrix.translate(0.0, 0.0, -5.0);
}

GLDisplay::~GLDisplay()
{
    makeCurrent();
    delete m_geometry;
    delete m_particles;
    doneCurrent();
}

void GLDisplay::mousePressEvent(QMouseEvent *e)
{
    mousePressPosition = QVector2D(e->localPos());
}

void GLDisplay::mouseMoveEvent(QMouseEvent *e)
{
    if(e->MouseButtonPress)
    {
        QVector2D displacement(e->localPos().x()-mousePressPosition.x(),
                               e->localPos().y()-mousePressPosition.y());
        QVector2D absisca(1,0); QVector2D ordinates(0,1);
        float dota = QVector2D::dotProduct(displacement, absisca);
        float dotb = QVector2D::dotProduct(displacement, ordinates);
        if(e->buttons() == Qt::LeftButton)
        {
            if(fabs(dotb) > fabs(dota))
            {
                if(e->localPos().y() > mousePressPosition.y())
                    matrix.rotate(0.5, QVector3D(1,0,0));
                if(e->localPos().y() < mousePressPosition.y())
                    matrix.rotate(-0.5, QVector3D(1,0,0));
            }
            if(fabs(dota) > fabs(dotb))
            {
                if(e->localPos().x() > mousePressPosition.x())
                    matrix.rotate(0.5, QVector3D(0,1,0));
                if(e->localPos().x() < mousePressPosition.y())
                    matrix.rotate(-0.5, QVector3D(0,1,0));
            }
        }
        if(e->buttons() == Qt::RightButton)
        {
            if(fabs(dotb) > fabs(dota))
            {
                if(e->localPos().y() > mousePressPosition.y())
                    matrix.translate(0,-0.02,0);
                if(e->localPos().y() < mousePressPosition.y())
                    matrix.translate(0,0.02,0);
            }
            if(fabs(dota) > fabs(dotb))
            {
                if(e->localPos().x() > mousePressPosition.x())
                    matrix.translate(0.02,0,0);
                if(e->localPos().x() < mousePressPosition.y())
                    matrix.translate(-0.02,0,0);
            }
        }
        if(e->buttons() == Qt::MidButton)
        {
            if(e->localPos().y() > mousePressPosition.y())
                matrix.translate(0,0,0.02);
            if(e->localPos().y() < mousePressPosition.y())
                matrix.translate(0,0,-0.02);
        }
    }
    update();
}

void GLDisplay::mouseReleaseEvent(QMouseEvent *e)
{
    e =e;
}

void GLDisplay::timerEvent(QTimerEvent *e)
{
    e = e;
    update();
}

void GLDisplay::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();

    glEnable(GL_DEPTH_TEST);

    m_geometry = new Triangle();
    m_particles = new Particles();

    timer.start(12, this);
}

void GLDisplay::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    projection.setToIdentity();

    projection.perspective(fov, aspect, zNear, zFar);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.setUniformValue("mvp_matrix", projection * matrix);
    m_geometry->drawTriangle(&program);
    m_particles->drawParticles(&program);
}

void GLDisplay::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple.vert"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple.frag"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
