#version 330 core

in vec3 vColor;

out vec4 FragColor;

uniform vec4 uColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}