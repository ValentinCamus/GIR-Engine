#version 410 core

layout (triangles) in;

layout (triangle_strip, max_vertices=18) out;
layout(location = 0) out vec4 fragPosition;

uniform mat4 vp[6];

void main() {
    for(int i = 0; i < 6; ++i) {
        gl_Layer = i;
        for(int j = 0; j < 3; ++j) {
            fragPosition = gl_in[j].gl_Position;

            gl_Position = vp[i] * fragPosition;
            EmitVertex();
        }
        EndPrimitive();
    }
}