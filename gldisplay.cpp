#include "gldisplay.h"

#include <iostream>
#include <cmath>

#include <QMouseEvent>

GLDisplay::GLDisplay(QWidget *parent):
    QOpenGLWidget(parent),
    m_geometry(0),
    m_particles(0),
    m_mesh(0)
{
    matrix.translate(0.0, 0.0, -5.0);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(16);
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);
    this->setFormat(format);
}

GLDisplay::~GLDisplay()
{
    makeCurrent();
    delete m_geometry;
    delete m_particles;
    delete m_mesh;
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

    normal = matrix.normalMatrix();
    update();
}

void GLDisplay::mouseReleaseEvent(QMouseEvent *e)
{
    e = e;
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

//    m_geometry = new Triangle();
//    m_particles = new Particles();
    m_mesh = new Mesh("");

    timer.start(12, this);
}

void GLDisplay::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 3.0, zFar = 30.0, fov = 45.0;

    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.setUniformValue("normal_matrix", normal);

    program.setUniformValue("mvp_matrix", projection * matrix);

    m_lightPosLoc = program.uniformLocation("lightPos");
    program.setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

//    m_geometry->drawTriangle(&program);
//    m_particles->drawParticles(&program);
    m_mesh->drawMesh(&program);
}

void GLDisplay::initShaders()
{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple.vert"))
        close();

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple.frag"))
        close();

    if (!program.link())
        close();

    if (!program.bind())
        close();
}
