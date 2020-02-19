#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoordinates;

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 viewProjection;

void main() {
    position = vec3(model * vec4(inPosition, 1.f));

    gl_Position = viewProjection * vec4(position, 1.f);

    normal = inNormal;
    textureCoordinates = inTextureCoordinates;
}