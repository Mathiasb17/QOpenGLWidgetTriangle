attribute vec4 a_position;
attribute vec3 a_normal;

uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;

uniform vec4 objectColor;
uniform vec3 lightPos;

varying vec3 vertex;
varying vec3 vertexNormal;
varying vec4 col;

void main(void)
{
    gl_Position = mvp_matrix * a_position;

    vertex = a_position;
    vertexNormal = a_normal;
    col = vec4(objectColor.x, objectColor.y, objectColor.z, 1);
}
