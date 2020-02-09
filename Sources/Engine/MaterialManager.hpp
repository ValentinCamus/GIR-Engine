#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

#include <Core/Core.hpp>
#include "Material.hpp"

namespace gir
{
    using MaterialUptr = std::unique_ptr<Material>;

    class MaterialManager
    {
    public:
        static const Material* GetMaterial(const std::string& name);

        // TODO
        static void AddMaterial();

    private:
        static std::vector<MaterialUptr> m_materials;
    };
} // namespace gir

#endif