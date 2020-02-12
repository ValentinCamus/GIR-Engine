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
    float cosInnerAngle;
    float cosOuterAngle;
};

float linearizeDepth(float near, float far, float z) { 
    z = 2.f * z - 1.f;
    return near / (far - z * (far - near));
}

float linearizeDepth(Light l, float z) {
    switch(l.type) {
        case POINT_LIGHT: 
        case SPOT_LIGHT: return linearizeDepth(NEAR_Z, FAR_Z, z);
        default: return z;
    }
}

vec3 lightVector(Light l, vec3 position) {
    switch(l.type) {
        case POINT_LIGHT: return normalize(l.position - position);
        case SPOT_LIGHT: return normalize(l.position - position);
        case DIRECTIONAL_LIGHT: return -l.direction;
        default: return vec3(0.f);
    }
}

float distanceAttenuation(Light l, float dist) {
    // float distToRange = dist / l.range;
    // float attenuation = max(1 - (distToRange * distToRange * distToRange * distToRange), 0.f);

    // TODO: Tweak (1/dist^2 gives a really huge attenuation)
    return 1 / (dist * dist);
}

float radialAttenuation(const Light light, const vec3 lightVector) {
    float cosLightDirAngle = dot(lightVector, -light.direction);

    return smoothstep(light.cosOuterAngle, light.cosInnerAngle, cosLightDirAngle);
}

float attenuation(Light l, vec3 lightVector, vec3 position) {
    switch(l.type) {
        case POINT_LIGHT: return distanceAttenuation(l, distance(position, l.position));
        case SPOT_LIGHT: return distanceAttenuation(l, distance(position, l.position)) * radialAttenuation(l, lightVector);
        default: return 1.f;
    }
}

#endif