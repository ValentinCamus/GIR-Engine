#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outAlbedo;
layout (location = 3) out vec3 outMetalnessRoughnessAlpha;


struct Material {
    bool hasNormalMap;
    bool hasAlbedoMap;
    bool hasMetalnessMap;
    bool hasRoughnessMap;
    bool hasAlphaMap;

    sampler2D normalMap;
    sampler2D albedoMap;
    sampler2D metalnessMap;
    sampler2D roughnessMap;
    sampler2D alphaMap;
    
    vec3 albedo;
    float metalness;
    float roughness;
    float alpha;
};

uniform Material m;

void main() {
    outPosition = position;

    float alpha = m.hasAlphaMap ? texture(m.alphaMap, textureCoord).x : m.alpha;

    if(alpha < 0.25)
        discard;
    
    outNormal = vec3(m.hasNormalMap ? mat3(tangent, bitangent, normal) * normalize(texture(m.normalMap, textureCoord).xyz) : normal);
    outAlbedo = m.hasAlbedoMap ? texture(m.albedoMap, textureCoord).xyz : m.albedo;

    float metalness = m.hasMetalnessMap ? texture(m.metalnessMap, textureCoord).x : m.metalness;
    float roughness = m.hasRoughnessMap ? texture(m.roughnessMap, textureCoord).x : m.roughness;
    outMetalnessRoughnessAlpha = vec3(metalness, roughness, alpha);
}