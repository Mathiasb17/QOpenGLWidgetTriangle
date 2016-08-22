#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <iostream>
#include <vector>
#include <string>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh : protected QOpenGLFunctions
{
public:
    Mesh(std::string mesh_path);
    virtual ~Mesh();

    void drawMesh(QOpenGLShaderProgram *program);

    void loadMesh();

private:
    void initMesh();

    QVector4D color;

    std::string m_mesh_path;

    std::vector<QVector3D> m_vertices;
    std::vector<QVector2D> m_texcoord;
    std::vector<unsigned int> m_faces;
    std::vector<QVector3D> m_normals;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLBuffer normalBuf;
};

#endif // MESH_H
