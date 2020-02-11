#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Texture/Texture2D.hpp>

namespace gir
{
    class Material : public Component
    {
    public:
        enum class EAttribute
        {
            Diffuse = 0,
            Specular = 1,
            Normal = 2,
            EAttributeCount
        };

        struct Attribute
        {
            Vec4f color = Vec4f(1.0f);
            Texture2D* texture = nullptr;
        };

    public:
        explicit Material(const std::string& name) :
            Component(name)
        {
            Logger::Info("Creating Material: {0}", name);
            Reset();
        }

        inline bool operator==(const Material& material) const { return GetName() == material.GetName(); }

        inline void SetAttribute(Material::EAttribute attribute, Vec4f color)
        {
            GIR_ASSERT(attribute < Material::EAttribute::EAttributeCount, "Invalid attribute");
            m_attributes[attribute] = {color, nullptr};
        }

        inline void SetAttribute(Material::EAttribute attribute, Texture2D* texture)
        {
            GIR_ASSERT(attribute < Material::EAttribute::EAttributeCount, "Invalid attribute");
            m_attributes[attribute] = {Vec4f(1.0f), texture};
        }

        inline void SetAttribute(Material::EAttribute attribute, const Material::Attribute& attr)
        {
            GIR_ASSERT(attribute < Material::EAttribute::EAttributeCount, "Invalid attribute");
            m_attributes[attribute] = attr;
        }

        inline const Material::Attribute& GetAttribute(Material::EAttribute attr) const
        {
            GIR_ASSERT(attr < Material::EAttribute::EAttributeCount, "Invalid attribute");
            return m_attributes.at(attr);
        }

        inline void Reset()
        {
            m_attributes.clear();
            for (unsigned i = 0; i < unsigned(Material::EAttribute::EAttributeCount); ++i)
            {
                m_attributes.insert({static_cast<EAttribute>(i), Attribute()});
            }
        }

    private:
        std::unordered_map<Material::EAttribute, Attribute> m_attributes = {};
    };

} // namespace gir
