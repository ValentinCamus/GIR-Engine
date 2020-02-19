#version 410 core

#include "Material.glsl"

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec4 outNormalMetalness;
layout (location = 2) out vec4 outAlbedoRoughness;

uniform Material material;

void main() {
    outPosition = position;

    float alpha = material.hasAlphaMap ? texture(material.alphaMap, textureCoord).x : material.alpha;

    if(alpha < 0.15)
        discard;

    float metalness = material.hasMetalnessMap ? texture(material.metalnessMap, textureCoord).x : material.metalness;
    float roughness = material.hasRoughnessMap ? texture(material.roughnessMap, textureCoord).x : material.roughness;
    
    outNormalMetalness = vec4(normal, metalness);
    outAlbedoRoughness = vec4(material.hasAlbedoMap ? texture(material.albedoMap, textureCoord).xyz : material.albedo, roughness);
}