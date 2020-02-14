#version 410 core

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D positions;
uniform sampler2D normals;
uniform sampler2D albedos;
uniform sampler2D metalnessRoughnessAlpha;

void main()
{
    fragColor = vec4(texture(albedos, textureCoordinates).xyz, 1.0);
}