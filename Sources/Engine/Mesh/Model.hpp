#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    using MaterialMeshes = std::pair<Material *, std::vector<Mesh *>>;

    class Model : public Component
    {
    public:
        Model(const std::string &name);

        void AddMesh(Mesh *mesh);

        unsigned MaterialCount() const;

        Material *GetMaterial(unsigned i) const;

        const std::vector<Mesh *> GetMeshes(unsigned i) const;

    private:
        // We could work with just a vector of vectors if we checked the material on say the first element of each
        // mesh vector
        std::vector<MaterialMeshes> m_meshesByMaterial;
    };

} // namespace gir
