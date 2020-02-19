#version 410 core

#include "Light.glsl"

layout (location = 0) in vec4 fragPosition;

uniform vec3 lightPosition;

void main() {
    gl_FragDepth = length(fragPosition.xyz - lightPosition) / FAR_Z;
}
