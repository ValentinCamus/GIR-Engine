#ifndef ALIT_LIGHT_GLSL
#define ALIT_LIGHT_GLSL

struct Material {
    bool hasAlbedoMap;
    bool hasMetalnessMap;
    bool hasRoughnessMap;
    bool hasAlphaMap;

    sampler2D albedoMap;
    sampler2D metalnessMap;
    sampler2D roughnessMap;
    sampler2D alphaMap;
    
    vec3 albedo;
    float metalness;
    float roughness;
    float alpha;
};

#endif