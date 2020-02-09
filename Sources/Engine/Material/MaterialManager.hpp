#pragma once

#include <Core/Core.hpp>
#include <Engine/Material/Material.hpp>

namespace gir
{
    using MaterialUptr = std::unique_ptr<Material>;

    class MaterialManager
    {
    public:
        static const Material* Get(const std::string& name);

        static void Add(const Material* material);

        static bool Remove(const std::string& name);

        static bool Remove(const Material* material);

        static bool Contains(const std::string& name);

        static bool Contains(const Material* material);

    private:
        static std::vector<MaterialUptr> m_materials;
    };
} // namespace gir