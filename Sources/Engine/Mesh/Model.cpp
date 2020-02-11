#include "Model.hpp"
#include "Engine/Manager/Manager.hpp"

namespace gir
{
    Model::Model(const std::string &name) : Component(name), m_meshesByMaterial() {}

    void Model::AddMesh(Mesh *mesh)
    {
        auto predicate = [mesh](const MaterialMeshes &materialMeshes) {
            return materialMeshes.first == mesh->GetMaterial();
        };

        auto it = std::find_if(m_meshesByMaterial.begin(), m_meshesByMaterial.end(), predicate);

        if (it == m_meshesByMaterial.end())
            m_meshesByMaterial.emplace_back(mesh->GetMaterial(), std::vector<Mesh *> {mesh});
        else
            it->second.emplace_back(mesh);
    }

    unsigned Model::MaterialCount() const { return static_cast<unsigned>(m_meshesByMaterial.size()); }

    Material *Model::GetMaterial(unsigned i) const { return m_meshesByMaterial[i].first; }

    const std::vector<Mesh *> Model::GetMeshes(unsigned i) const { return m_meshesByMaterial[i].second; }

} // namespace gir