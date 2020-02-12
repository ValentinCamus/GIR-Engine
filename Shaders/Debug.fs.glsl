#version 410 core

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D positions;
uniform sampler2D normals;
uniform sampler2D diffuseColor;
uniform sampler2D specularColor;
uniform sampler2D specularParameters;

void main()
{
    // Just so none of the uniform is optimized away
    vec3 color = vec3(texture(specularParameters, textureCoordinates).xy, 0.f);
    fragColor = vec4(normalize(texture(positions, textureCoordinates).xyz
                    + texture(normals, textureCoordinates).xyz
                    + texture(diffuseColor, textureCoordinates).xyz
                    + texture(specularColor, textureCoordinates).xyz
                    + color), 1.0);
}