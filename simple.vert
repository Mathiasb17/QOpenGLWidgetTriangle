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

    col = vec4(abs(lightPos.x), abs(lightPos.y), abs(lightPos.z), 1);

    vertex = a_position;
    vertexNormal = a_normal;
}
