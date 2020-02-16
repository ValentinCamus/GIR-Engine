#version 410 core

#define MAX_LIGHTS 5
#define PI 3.14159265359f

#include "Light.glsl"

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D position;
uniform sampler2D normalMetalness;
uniform sampler2D albedoRoughness;

uniform vec3 cameraPosition;
uniform uint lightCount;
uniform Light lights[MAX_LIGHTS];

float distributionGGX(vec3 normal, vec3 halfv, float roughness) {
    float roughnessSQ = roughness * roughness;

    float ndoth = max(dot(normal, halfv), 0);
    float coefficiant = ndoth * ndoth * (roughnessSQ - 1) + 1;

    return roughnessSQ / (PI * coefficiant * coefficiant);
}

float geometryGGXSchlickBeckmann(float ndotvec, float roughness) {
    float k = (roughness + 1);
    k = k * k / 8;

    return ndotvec / (ndotvec * (1 - k) + k);
}

float geometrySmith(float cosThetai, float cosThetao, float roughness) {
    return geometryGGXSchlickBeckmann(cosThetai, roughness) * geometryGGXSchlickBeckmann(cosThetao, roughness);
}

vec3 fresnelSchlick(vec3 view, vec3 halfv, vec3 f0) {
    return f0 + (1 - f0) * pow(1 - max(dot(view, halfv), 0), 5);
}

void main()
{
    vec4 normalM = texture(normalMetalness, textureCoordinates);
    vec4 albedoR = texture(albedoRoughness, textureCoordinates);
    vec3 position = texture(position, textureCoordinates).xyz;

    vec3 normal = normalM.xyz;
    vec3 albedo = albedoR.rgb;

    float metalness = normalM.w;
    float roughness = albedoR.w;

    fragColor = vec4(0);

    for(int i = 0; i < lightCount; ++i) {
        vec3 wi = lightVector(lights[i], position);
        vec3 wo = normalize(cameraPosition - position);
        vec3 halfv = normalize(wo + wi);

        float cosThetai = max(dot(normal, wi), 0.004);
        float cosThetao = max(dot(normal, wo), 0.004);

        vec3 Li = lights[i].color * attenuation(lights[i], wi, position);
    
        vec3 f0 = mix(vec3(0.04), albedo, metalness);
    
        vec3 fresnel = fresnelSchlick(wo, halfv, f0);
        vec3 kd = (1 - fresnel) * (1 - metalness);
    
        vec3 cookTorrance = distributionGGX(normal, halfv, roughness) * fresnel * geometrySmith(cosThetai, cosThetao, roughness);
        vec3 lambert = albedo / PI;

        float denominator = 4 * cosThetai * cosThetao;

        fragColor += vec4((kd * lambert + cookTorrance / denominator) * Li * cosThetai, 1);
    }

    fragColor.rgb = fragColor.rgb / (fragColor.rgb + 1);
}