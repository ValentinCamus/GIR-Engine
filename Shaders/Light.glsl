#ifndef ALIT_LIGHT_GLSL
#define ALIT_LIGHT_GLSL

#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define SPOT_LIGHT 2

#define NEAR_Z 0.4f
#define FAR_Z 45.f

#define MAX_LIGHTS 3
#define RSM_MAX_SAMPLE_COUNT 400

struct Light {
    uint type;

    vec3 color;
    vec3 position;
    vec3 direction;
    float cosInnerAngle;
    float cosOuterAngle;

    sampler2DShadow depthSM;
    sampler2D positionSM;
    sampler2D normalSM;
    sampler2D fluxSM;

    samplerCubeShadow depthSMPL;
    samplerCube positionSMPL;
    samplerCube normalSMPL;
    samplerCube fluxSMPL;

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
    position.xyz += normal * 0.1;

    switch(light.type) {
        case POINT_LIGHT:
            // LearnOpenGL PCF, not perfect but does the job for now
            vec3 direction = position.xyz - light.position;
            float depth = length(direction) / FAR_Z;
            
            vec3 sampleOffsetDirections[20] = vec3[]( vec3( 1.f,  1.f,  1.f), vec3( 1.f, -1.f,  1.f), vec3(-1.f, -1.f,  1.f), vec3(-1.f,  1.f,  1.f), 
                                                      vec3( 1.f,  1.f, -1.f), vec3( 1.f, -1.f, -1.f), vec3(-1.f, -1.f, -1.f), vec3(-1.f,  1.f, -1.f),
                                                      vec3( 1.f,  1.f,  0.f), vec3( 1.f, -1.f,  0.f), vec3(-1.f, -1.f,  0.f), vec3(-1.f,  1.f,  0.f),
                                                      vec3( 1.f,  0.f,  1.f), vec3(-1.f,  0.f,  1.f), vec3( 1.f,  0.f, -1.f), vec3(-1.f,  0.f, -1.f),
                                                      vec3( 0.f,  1.f,  1.f), vec3( 0.f, -1.f,  1.f), vec3( 0.f, -1.f, -1.f), vec3( 0.f,  1.f, -1.f)); 
            
            for(int i = 0; i < 20; ++i) {
                result += texture(light.depthSMPL, vec4(direction + sampleOffsetDirections[i] * (1.f + depth) / FAR_Z, depth));
            }

            result = result / 20;
            break;

        case SPOT_LIGHT:
        case DIRECTIONAL_LIGHT: 
            position = light.viewProjection * position;
            position /= position.w;
            position = position * 0.5f + 0.5f;
            vec2 texelSize = 1.f / textureSize(light.depthSM, 0);

            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    result += texture(light.depthSM, vec3(position.xy + vec2(i - 1.5f, j - 1.5f) * texelSize, position.z));
                }
            }

            result = result / 16.f;
            break;

        default: 
            result = 1.f;
            break;
    }

    return result;
}

vec3 indirect(Light light, vec4 position, vec3 normal, uint sampleCount, vec3 samples[RSM_MAX_SAMPLE_COUNT]){
    vec3 result = vec3(0.f);
    
    switch(light.type) {
        case POINT_LIGHT:
            break;

        case SPOT_LIGHT:
        case DIRECTIONAL_LIGHT: 
            vec4 textureCoord = light.viewProjection * position;
            textureCoord /= textureCoord.w;
            textureCoord = textureCoord * 0.5f + 0.5f;

            for(int i = 0; i < sampleCount; ++i) {
                vec2 texCoord = textureCoord.xy + samples[i].xy;

                vec3 vplPosition = texture(light.positionSM, texCoord).xyz;
                vec3 vplNormal = texture(light.normalSM, texCoord).xyz;
                vec3 vplFlux = texture(light.fluxSM, texCoord).rgb;

                vec3 lightVector = vplPosition - position.xyz;

                result += samples[i].z * vplFlux * max(dot(vplNormal, lightVector), 0.f) * max(-dot(normal, lightVector), 0.f) / pow(length(lightVector), 4.f);
            }

            result /= sampleCount;
            break;

        default: 
            break;
    }

    return result;
}

#endif