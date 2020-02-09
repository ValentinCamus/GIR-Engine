#version 330 core

out vec4 FragColor;

in vec3 vColor;

uniform vec4 uColor;

void main()
{
    FragColor = uColor + vec4(vColor, 1.0);
}