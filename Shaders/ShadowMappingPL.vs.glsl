#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoordinates;

uniform mat4 model;

void main() {
    gl_Position = model * vec4(inPosition, 1.f);
}