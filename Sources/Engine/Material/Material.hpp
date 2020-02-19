#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Texture/Texture.hpp>
#include <Engine/Shader/Shader.hpp>

namespace gir
{
    class Material : public Component
    {
    public:
        enum class EAttribute
        {
            ALBEDO    = 0,
            METALNESS = 1,
            ROUGHNESS = 2,
            ALPHA     = 3,
            EAttributeCount
        };

        struct Attribute
        {
            Vec4f color        = Vec4f(1.0f);
            Texture* texture = nullptr;
        };

    public:
        explicit Material(const std::string& name) : Component(name)
        {
            Logger::Info("Creating Material: {0}", name);
            Reset();
        }

        inline bool operator==(const Material& material) const { return GetName() == material.GetName(); }

        // That's a big boy for an header but whatever
        // Also it could most likely be cleaner
        inline void SetUniforms(const std::string& name, Shader* shader, int slot)
        {
            for (int i = 0; i < static_cast<int>(m_attributes.size()); ++i)
            {
                Attribute attr = m_attributes[i];
                if (attr.texture) attr.texture->Bind(slot + i);

                switch (static_cast<EAttribute>(i))
                {
                    case EAttribute::ALBEDO:
                        shader->SetUniform(name + ".hasAlbedoMap", static_cast<bool>(attr.texture));

                        if (attr.texture)
                            shader->SetUniform(name + ".albedoMap", i);
                        else
                            shader->SetUniform(name + ".albedo", Vec3f(attr.color));

                        break;

                    case EAttribute::METALNESS:
                        shader->SetUniform(name + ".hasMetalnessMap", static_cast<bool>(attr.texture));

                        if (attr.texture)
                            shader->SetUniform(name + ".metalnessMap", i);
                        else
                            shader->SetUniform(name + ".metalness", attr.color.r);

                        break;

                    case EAttribute::ROUGHNESS:
                        shader->SetUniform(name + ".hasRoughnessMap", static_cast<bool>(attr.texture));

                        if (attr.texture)
                            shader->SetUniform(name + ".roughnessMap", i);
                        else
                            shader->SetUniform(name + ".roughness", attr.color.r);

                        break;

                    case EAttribute::ALPHA:
                        shader->SetUniform(name + ".hasAlphaMap", static_cast<bool>(attr.texture));

                        if (attr.texture)
                            shader->SetUniform(name + ".alphaMap", i);
                        else
                            shader->SetUniform(name + ".alpha", attr.color.r);

                        break;

                    default:
                        Logger::Error("Material::SetUniforms: Invalid attribute type");
                        break;
                }
            }
        }

        inline void UnbindTextures()
        {
            for (auto attr : m_attributes)
                if (attr.texture) attr.texture->Unbind();
        }

        inline void SetAttribute(Material::EAttribute attribute, Vec4f color)
        {
            GIR_ASSERT(attribute < Material::EAttribute::EAttributeCount, "Invalid attribute");
            m_attributes[static_cast<int>(attribute)] = {color, nullptr};
        }

        inline void SetAttribute(Material::EAttribute attribute, Texture* texture)
        {
            GIR_ASSERT(attribute < Material::EAttribute::EAttributeCount, "Invalid attribute");
            m_attributes[static_cast<int>(attribute)] = {Vec4f(1.0f), texture};
        }

        inline void SetAttribute(Material::EAttribute attribute, const Material::Attribute& attr)
        {
            GIR_ASSERT(attribute < Material::EAttribute::EAttributeCount, "Invalid attribute");
            m_attributes[static_cast<int>(attribute)] = attr;
        }

        inline const Material::Attribute& GetAttribute(Material::EAttribute attr) const
        {
            GIR_ASSERT(attr < Material::EAttribute::EAttributeCount, "Invalid attribute");
            return m_attributes[static_cast<int>(attr)];
        }

        inline void Reset()
        {
            m_attributes = std::vector<Attribute>(static_cast<int>(Material::EAttribute::EAttributeCount));
        }

    private:
        std::vector<Attribute> m_attributes = {};
    };
} // namespace gir
