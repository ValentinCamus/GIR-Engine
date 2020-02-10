#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    class Model : public Component
    {
    public:
        Model(const std::string& name);

    private:
        std::vector<std::pair<Material*, Mesh>> m_meshesByMaterial;
    };

} // namespace gir
