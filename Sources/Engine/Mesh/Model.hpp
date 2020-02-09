#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    class Model : public Component
    {
    public:


    private:
        // FIXME: Mesh or Mesh& or Mesh* ?
        std::vector<Mesh*> m_meshes;
    };

} // namespace gir
