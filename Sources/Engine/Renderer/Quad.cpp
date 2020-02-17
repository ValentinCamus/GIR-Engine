#include "Quad.hpp"

#define QUAD_VERTICES                               \
    {                                               \
        {{ 1.f,  1.f, 0.0f}, Vec3f(), {1.f, 1.f}},  \
        {{ 1.f, -1.f, 0.0f}, Vec3f(), {1.f, 0.f}},  \
        {{-1.f, -1.f, 0.0f}, Vec3f(), {0.f, 0.f}},  \
        {{-1.f,  1.f, 0.0f}, Vec3f(), {0.f, 1.f}},  \
    }                                               \

#define QUAD_INDICES {1, 0, 2, 2, 0, 3}

namespace gir
{
    Quad::Quad(const std::string &name)
        : Mesh(name, QUAD_INDICES, QUAD_VERTICES)
    {

    }
}