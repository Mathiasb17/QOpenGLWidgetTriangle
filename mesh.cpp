#include "mesh.h"

#include <fstream>
#include <sstream>

Mesh::Mesh(std::string mesh_path):
    indexBuf(QOpenGLBuffer::IndexBuffer),
    m_mesh_path(mesh_path)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initMesh();
}

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Mesh::initMesh()
{
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<GLushort>  indices;
    std::vector<QVector2D> texcoords;

    loadMesh(positions, normals, indices, texcoords);
}

void Mesh::loadMesh(std::vector<QVector3D> &positions, std::vector<QVector3D> &normals, std::vector<GLushort> &indices, std::vector<QVector2D> &texcoords)
{
    std::fstream mesh_file;
    mesh_file.open(m_mesh_path.c_str(), std::ios_base::in);

    char line[255];
    while(mesh_file.getline(line, 255))
    {
        std::istringstream sline;
        std::cout << line << std::endl;
    }
}

void Mesh::drawMesh(QOpenGLShaderProgram *program)
{

}
