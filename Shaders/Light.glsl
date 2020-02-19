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

    sampler2DShadow shadowmap;
    samplerCubeShadow shadowmapPL;

    // For spotlights and directionnal lights
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

float distanceAttenuation(vec3 position, Light light) {
    float dist = distance(position, light.position);
    return 1 / (dist * dist);
}

float radialAttenuation(const Light light, const vec3 lightVector) {
    float cosLightDirAngle = dot(lightVector, -light.direction);

    return smoothstep(light.cosOuterAngle, light.cosInnerAngle, cosLightDirAngle);
}

float attenuation(Light light, vec3 lightVector, vec3 position) {
    switch(light.type) {
        case POINT_LIGHT: return distanceAttenuation(position, light);
        case SPOT_LIGHT: return distanceAttenuation(position, light) * radialAttenuation(light, lightVector);
        default: return 1;
    }
}

float shadow(Light light, vec4 position, vec3 normal) {
    float result = 0;
    position.xyz += normal * 0.125;

    switch(light.type) {
        case POINT_LIGHT:
            // LearnOpenGL PCF, not perfect but does the job for now
            vec3 direction = position.xyz - light.position;
            float depth = length(direction) / FAR_Z;
            
            vec3 sampleOffsetDirections[20] = vec3[]( vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
                                                      vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
                                                      vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
                                                      vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
                                                      vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)); 
            
            for(int i = 0; i < 20; ++i) {
                result += texture(light.shadowmapPL, vec4(direction + sampleOffsetDirections[i] * (1 + depth) / FAR_Z, depth));
            }

            result = result / 20;

            break;

        case SPOT_LIGHT:
        case DIRECTIONAL_LIGHT: 
            position = light.viewProjection * position;
            position /= position.w;
            position = position * 0.5 + 0.5;
            vec2 texelSize = 1 / textureSize(light.shadowmap, 0);

            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    result += texture(light.shadowmap, vec3(position.xy + vec2(i - 1.5, j - 1.5) * texelSize, position.z));
                }
            }

            result = result / 16;

            break;

        default: 
            result = 1;
            break;
    }

    return result;
}

#endif