#include "mesh.h"

#include <fstream>
#include <sstream>

#include <cstdio>
#include <cstdlib>

#include <QFile>

Mesh::Mesh(std::string mesh_path):
    indexBuf(QOpenGLBuffer::IndexBuffer),
    m_mesh_path(mesh_path)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    normalBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initMesh();

    color = QVector4D(0,0,1,1);
}

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    normalBuf.destroy();
}

void Mesh::initMesh()
{
    loadMesh();

    arrayBuf.bind();
    arrayBuf.allocate(m_vertices.data(), m_vertices.size() * sizeof(QVector3D));

    indexBuf.bind();
    indexBuf.allocate(m_faces.data(), m_faces.size() * sizeof(unsigned int));

    normalBuf.bind();
    std::cout << "norm size " << m_normals.size() << std::endl;
    normalBuf.allocate(m_normals.data(), m_normals.size() * sizeof(QVector3D));
}

void Mesh::loadMesh()
{
    const aiScene* scene = aiImportFile( "/home/mathias/Documents/QOpenGLWidgetTriangle/teapot.obj",
                                         aiProcess_CalcTangentSpace       |
                                         aiProcess_GenNormals             |
                                         aiProcess_Triangulate            |
                                         aiProcess_JoinIdenticalVertices  |
                                         aiProcess_SortByPType);

      if( !scene)
      {
        std::cout << aiGetErrorString() << std::endl;
        exit(1);
      }

      //loop over meshes
      for (int i = 0; i < scene->mNumMeshes; ++i)
      {
          //loop into current mesh for vertices
          for (int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
          {
              QVector3D p = QVector3D(scene->mMeshes[i]->mVertices[j].x,
                                      scene->mMeshes[i]->mVertices[j].y,
                                      scene->mMeshes[i]->mVertices[j].z);
              m_vertices.push_back(p);
          }

          //loop into current mesh for indices
          for (int j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
          {
              aiFace f = scene->mMeshes[i]->mFaces[j];
              for (int k = 0; k < f.mNumIndices; ++k)
              {
                  m_faces.push_back(f.mIndices[k]);
              }
          }

          //loop into current mesh for normals, one normal per vertex
          for (int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
          {
              QVector3D m = QVector3D(scene->mMeshes[i]->mNormals[j].x,
                                      scene->mMeshes[i]->mNormals[j].y,
                                      scene->mMeshes[i]->mNormals[j].z);
              m_normals.push_back(m);
          }
      }
      aiReleaseImport( scene);
}

void Mesh::drawMesh(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    program->setUniformValue("objectColor", color);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    int normalLocation = program->attributeLocation("a_normal");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    normalBuf.bind();
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, m_faces.size(), GL_UNSIGNED_INT, 0);
}
