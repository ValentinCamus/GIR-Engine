#include "Model.hpp"
#include "Engine/Manager/Manager.hpp"

namespace gir
{
    Model::Model(const std::string &name) : Component(name), m_meshesByMaterial() {}

    void Model::AddMesh(Element element)
    {
        auto predicate = [&element](const MaterialMeshes &materialMeshes) {
            return materialMeshes.first == element.first;
        };

        auto it = std::find_if(m_meshesByMaterial.begin(), m_meshesByMaterial.end(), predicate);

        if (it == m_meshesByMaterial.end())
            m_meshesByMaterial.emplace_back(element.first, std::vector<Mesh *> {element.second});
        else
            it->second.emplace_back(element.second);
    }

    unsigned Model::MaterialCount() const { return static_cast<unsigned>(m_meshesByMaterial.size()); }

    Material *Model::GetMaterial(unsigned i) const { return m_meshesByMaterial[i].first; }

    const std::vector<Mesh *> Model::GetMeshes(unsigned i) const { return m_meshesByMaterial[i].second; }

} // namespace gir