varying vec4 col;

//void main(void)
//{
//    gl_FragColor = col;
//}

varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;

void main()
{
    highp vec3 L = normalize(lightPos - vert);
    highp float NL = max(dot(normalize(vertNormal), L), 0.0);
    highp vec4 color = clamp(col * 0.2 + col * 0.8 * NL, 0.0, 1.0);
    gl_FragColor = col;
}
