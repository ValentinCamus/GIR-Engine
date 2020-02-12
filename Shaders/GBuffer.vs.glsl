#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoord;
layout (location = 3) in vec3 inTangent;
layout (location = 4) in vec3 inBitangent;

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec2 textureCoord;
layout (location = 3) out vec3 tangent;
layout (location = 4) out vec3 bitangent;


uniform mat4 vp;
uniform mat4 model;


void main() {
    position = (model * vec4(inPosition, 1.f)).xyz;
    gl_Position = vp * vec4(position, 1.f);

    textureCoord = inTextureCoord;

    // Incorrect for non uniform scaling
    normal = normalize((model * vec4(inNormal, 0.f)).xyz);
    bitangent = normalize((model * vec4(inBitangent, 0.f)).xyz);
    tangent = normalize((model * vec4(inBitangent, 0.f)).xyz);
    // tangent = normalize(cross(bitangent, normal)); // Workaround for assimp generating only the bitangent in some of my models
}