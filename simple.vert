attribute vec4 a_position;
attribute vec3 a_normal;

uniform mat4 mvp_matrix;
uniform vec4 objectColor;
uniform vec3 lightPos;

varying vec4 col;

void main(void)
{
    gl_Position = mvp_matrix * a_position;
    vec4 c = vec4(abs(a_normal.x), abs(a_normal.y), abs(a_normal.z), 1);
    col = c;
}
