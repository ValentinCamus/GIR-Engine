#include "MaterialManager.hpp"

namespace gir
{
    const Material* MaterialManager::GetMaterial(const std::string& name) { return m_materials[name]; }

    // TODO
    void MaterialManager::AddMaterial() {}
} // namespace gir