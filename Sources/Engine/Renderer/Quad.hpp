#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>

namespace gir
{
    class Quad : public Mesh
    {
    public:
        explicit Quad(const std::string& name);
    };
}