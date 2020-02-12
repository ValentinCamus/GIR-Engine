#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outDiffuseColor;
layout (location = 3) out vec3 outSpecularColor;
layout (location = 4) out vec2 outSpecularParameters;


struct Material {
    bool hasNormalTexture;
    bool hasKdTexture;
    bool hasKsTexture;
    bool hasAlphaTexture;

    sampler2D normalTexture;
    sampler2D kdTexture;
    sampler2D ksTexture;
    sampler2D alphaTexture;

    vec3 kd;
    vec3 ks;
    float ns;
    float nsStrength;
    float alpha;
};


uniform Material m;


void main() {
    outDiffuseColor = vec3(1.f, 0.f, 0.f);
//    float alpha = m.hasAlphaTexture ? texture(m.alphaTexture, textureCoord).x : m.alpha;
//
//    if(alpha < 0.25)
//        discard;
//
//    outNormal = vec3(m.hasNormalTexture ? mat3(tangent, bitangent, normal) * normalize(texture(m.normalTexture, textureCoord).xyz) : normal);
//    outDiffuseColor = m.hasKdTexture ? texture(m.kdTexture, textureCoord).xyz: m.kd;
//    outSpecularColor = m.hasKsTexture ? texture(m.ksTexture, textureCoord).xyz : m.ks;
//    outSpecularParameters = vec2(m.ns, m.nsStrength);
}