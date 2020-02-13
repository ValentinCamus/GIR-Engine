#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>

namespace gir
{
#define QUAD_VERTICES std::vector<Mesh::Vertex> {                                       \
            { Vec3f( 1.f,  1.f, 0.0f), Vec3f(), Vec2f(1.f, 1.f), Vec3f(), Vec3f() },    \
            { Vec3f( 1.f, -1.f, 0.0f), Vec3f(), Vec2f(1.f, 0.f), Vec3f(), Vec3f() },    \
            { Vec3f(-1.f, -1.f, 0.0f), Vec3f(), Vec2f(0.f, 0.f), Vec3f(), Vec3f() },    \
            { Vec3f(-1.f,  1.f, 0.0f), Vec3f(), Vec2f(0.f, 1.f), Vec3f(), Vec3f() },    \
    }

#define QUAD_INDICES std::vector<unsigned> {1, 0, 2, 2, 0, 3}

    class Quad
    {
    public:
        static inline std::unique_ptr<Mesh> Create(const std::string& name)
        {
            return std::make_unique<Mesh>(name, QUAD_VERTICES, QUAD_INDICES);
        }
    };

}