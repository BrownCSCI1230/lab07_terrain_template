#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 inColor;
out vec4 vert;
out vec4 norm;
out vec3 color;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main()
{
    color = inColor;
    vert = mvMatrix * vec4(vertex,1.0);
    norm = transpose(inverse(mvMatrix)) *  vec4(normal,0.0);
    gl_Position = projMatrix * mvMatrix * vec4(vertex,1.0);
}
