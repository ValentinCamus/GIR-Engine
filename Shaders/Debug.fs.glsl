#version 410 core

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D positionMap;
uniform sampler2D normalMetalness;
uniform sampler2D albedoRoughness;

void main()
{
    fragColor = vec4(texture(albedoRoughness, textureCoordinates).rgb, 1.0);
}