#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uDiffuse;

void main()
{
    FragColor = texture(uDiffuse, TexCoords);
}