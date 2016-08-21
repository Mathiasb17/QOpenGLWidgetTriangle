attribute vec4 a_position;
attribute vec3 a_normal;

uniform mat4 mvp_matrix;
uniform vec4 objectColor;

varying vec4 col;

void main(void)
{
    gl_Position = mvp_matrix * a_position;
    col = objectColor;
}
