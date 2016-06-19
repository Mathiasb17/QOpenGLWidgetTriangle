#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <iostream>
#include <vector>
#include <string>


class Mesh : protected QOpenGLFunctions
{
public:
    Mesh(std::string mesh_path);
    virtual ~Mesh();

    void drawMesh(QOpenGLShaderProgram *program);

    void loadMesh(std::vector<QVector3D> &positions, std::vector<QVector3D> &normals, std::vector<GLushort> &indices, std::vector<QVector2D> &texcoords);

private:
    void initMesh();

    QVector4D color;

    std::string m_mesh_path;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // MESH_H
