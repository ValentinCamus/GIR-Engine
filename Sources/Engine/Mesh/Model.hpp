#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    using MaterialMeshes = std::pair<Material *, std::vector<Mesh *>>;
    using Element = std::pair<Material *, Mesh*>;

    class Model : public Component
    {
    public:
        Model(const std::string &name);

        void AddMesh(Element element);

        unsigned MaterialCount() const;

        Material *GetMaterial(unsigned i) const;

        const std::vector<Mesh *> GetMeshes(unsigned i) const;

    private:
        std::vector<MaterialMeshes> m_meshesByMaterial;
    };

} // namespace gir