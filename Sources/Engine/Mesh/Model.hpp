#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    class Model : public Component
    {
    public:
        struct Element
        {
            Mesh mesh;
            Material* material = nullptr;
        };

    public:
        explicit Model(const std::string& name);

        inline void AddMaterial(unsigned index, Material* material)
        {
            GIR_ASSERT(index < m_elements.size(), "Invalid element index");
            m_elements[index].material = material;
        }

        inline Material* GetMaterial(unsigned index) const
        {
            GIR_ASSERT(index < m_elements.size(), "Invalid element index");
            return m_elements[index].material;
        }

        inline const std::vector<Element>& GetElements() const { return m_elements; }

    private:
        std::vector<Element> m_elements = {};
    };

} // namespace gir
