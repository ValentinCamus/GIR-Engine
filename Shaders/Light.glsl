#ifndef ALIT_LIGHT_GLSL
#define ALIT_LIGHT_GLSL

#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define SPOT_LIGHT 2

#define NEAR_Z 0.2f
#define FAR_Z 100.f

struct Light {
    uint type;

    vec3 color;
    vec3 position;
    vec3 direction;
    // float range;
    float cosInnerAngle;
    float cosOuterAngle;

    sampler2DShadow shadowmap;
    samplerCubeShadow shadowmapPL;

    // For spotlights and directionnal lights
    mat4 projection;

    // For point lights
    mat4 viewProjection;
};

float linearizeDepth(float near, float far, float z) { 
    z = 2 * z - 1;
    return near / (far - z * (far - near));
}

float linearizeDepth(Light light, float z) {
    switch(light.type) {
        case POINT_LIGHT: 
        case SPOT_LIGHT: return linearizeDepth(NEAR_Z, FAR_Z, z);
        default: return z;
    }
}

vec3 lightVector(Light light, vec3 position) {
    switch(light.type) {
        case POINT_LIGHT: return normalize(light.position - position);
        case SPOT_LIGHT: return normalize(light.position - position);
        case DIRECTIONAL_LIGHT: return -light.direction;
        default: return vec3(0);
    }
}

float distanceAttenuation(Light light, float dist) {
    // float distToRange = dist / light.range;
    // float attenuation = max(1 - (distToRange * distToRange * distToRange * distToRange), 0);

    return 1 / (dist * dist);
}

float radialAttenuation(const Light light, const vec3 lightVector) {
    float cosLightDirAngle = dot(lightVector, -light.direction);

    return smoothstep(light.cosOuterAngle, light.cosInnerAngle, cosLightDirAngle);
}

float attenuation(Light light, vec3 lightVector, vec3 position) {
    switch(light.type) {
        case POINT_LIGHT: return distanceAttenuation(light, distance(position, light.position));
        case SPOT_LIGHT: return distanceAttenuation(light, distance(position, light.position)) * radialAttenuation(light, lightVector);
        default: return 1;
    }
}

float shadow(Light light, vec4 position, vec3 normal, vec3 wi) {
    position.xyz += normal * 0.125;

    switch(light.type) {
        case SPOT_LIGHT:
        case DIRECTIONAL_LIGHT: 
            position = light.viewProjection * position;
            position /= position.w;
            position = position * 0.5f + 0.5f;
            vec2 texelSize = 1.f / textureSize(light.shadowmap, 0);

            float result = 0.f;
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    result += texture(light.shadowmap, vec3(position.xy + vec2(i - 1.5, j - 1.5) * texelSize, position.z));
                }
            }

            return result / 16;

        default: 
            return 1;
    }
}

#endif