#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include "triangle.h"
#include "particles.h"

class GLDisplay : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);
    ~GLDisplay();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void initShaders();

private:
    //simulation loop
    QBasicTimer timer;

    //geometry
    Triangle *m_geometry;
    Particles *m_particles;

    //shaders
    QOpenGLShaderProgram program;

    //matrices
    QMatrix4x4 projection;
    QMatrix4x4 matrix;

    //mouse
    QVector2D mousePressPosition;
};

#endif // GLDISPLAY_H
