#version 410 core

#include "Light.glsl"

layout (location = 0) in vec2 textureCoordinates;

layout (location = 0) out vec4 fragColor;

uniform sampler2D positionMap;
uniform sampler2D normalMetalness;
uniform sampler2D albedoRoughness;

uniform vec3 cameraPosition;
uniform uint lightCount;
uniform Light lights[MAX_LIGHTS];

uniform int sampleCount;
uniform vec3 samples[RSM_MAX_SAMPLE_COUNT];

void main() {
    vec4 normalM = texture(normalMetalness, textureCoordinates);
    vec4 albedoR = texture(albedoRoughness, textureCoordinates);
    vec3 position = texture(positionMap, textureCoordinates).xyz;

    vec3 normal = normalM.xyz;
    vec3 albedo = albedoR.rgb;

    fragColor = vec4(0.f, 0.f, 0.f, 1.f);

    for(int i = 0; i < lightCount; ++i) 
        fragColor.rgb += indirect(lights[i], vec4(position, 1), normal, sampleCount, samples) * albedo;
}