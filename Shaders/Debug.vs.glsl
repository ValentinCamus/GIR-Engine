#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTextureCoordinates;

out vec3 vColor;

void main()
{
    vColor = aNormals;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}