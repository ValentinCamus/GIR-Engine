#version 410 core

#include "Light.glsl"

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinates;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outFlux;

uniform Light light;

uniform bool hasAlbedoMap;
uniform sampler2D albedoMap;
uniform vec3 albedo;

void main() {
    outPosition = position;
    outNormal = normal;

    float attenuation = (light.type == SPOT_LIGHT ? radialAttenuation(light, lightVector(light, position)) : 1.f);

    outFlux = light.color * (hasAlbedoMap ? texture(albedoMap, textureCoordinates).rgb : albedo) * attenuation;
}