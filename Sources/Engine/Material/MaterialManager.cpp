#include "MaterialManager.hpp"

namespace gir
{
    std::vector<MaterialUptr> MaterialManager::m_materials = {};

    const Material* MaterialManager::Get(const std::string& name)
    {
        // TODO
        return nullptr;
    }


    void MaterialManager::Add(const Material* material)
    {
        // TODO
    }

    bool MaterialManager::Remove(const std::string& name)
    {
        // TODO
        return false;
    }

    bool MaterialManager::Remove(const Material* material)
    {
        // TODO
        return false;
    }

    bool MaterialManager::Contains(const std::string& name)
    {
        // TODO
        return false;
    }

    bool MaterialManager::Contains(const Material* material)
    {
        // TODO
        return false;
    }

} // namespace gir