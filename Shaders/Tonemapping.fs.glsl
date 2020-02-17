#version 410 core

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D hdrColor;

void main() {
    vec4 color = texture(hdrColor, textureCoordinates);

    fragColor = color / (color + 1);
}