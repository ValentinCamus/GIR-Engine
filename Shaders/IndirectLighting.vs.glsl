#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoordinates;

layout (location = 0) out vec2 textureCoordinates;

uniform uint quadCount;
uniform uint quadLine;
uniform uint quadCol;

void main()
{
    gl_Position = vec4((inPosition + 1 + 2 * vec3(quadLine, quadCol, 0)) / quadCount - vec3(1.f, 1.f, 0.f), 1.f);

    textureCoordinates = (inTextureCoordinates + vec2(quadLine, quadCol)) / quadCount;
}