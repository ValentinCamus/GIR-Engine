#version 410 core

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D positions;
uniform sampler2D normals;
uniform sampler2D albedo;
uniform sampler2D metalnessRoughnessAlpha;

void main()
{
    fragColor = vec4(texture(albedo, textureCoordinates).xyz, 1.0);
}