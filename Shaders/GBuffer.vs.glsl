#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoord;

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec2 textureCoord;


uniform mat4 vp;
uniform mat4 model;


void main() {
    position = (model * vec4(inPosition, 1.f)).xyz;
    gl_Position = vp * vec4(position, 1.f);

    textureCoord = inTextureCoord;

    // Incorrect for non uniform scaling
    normal = normalize(mat3(model) * inNormal);
}