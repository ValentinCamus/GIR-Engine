#include "SpotLight.hpp"

namespace gir
{
    const Mat4f SpotLight::m_projection = glm::perspective(3 * PI / 4, 1.f, NEAR_Z, FAR_Z);

    SpotLight::SpotLight(const std::string &name,
                         const Mat4f &transform,
                         const Vec3f &color,
                         float innerAngle,
                         float outerAngle) :
            Light(name, transform, color),
            m_innerAngle(innerAngle),
            m_outerAngle(outerAngle),
            m_cosInnerAngle(cos(innerAngle)),
            m_cosOuterAngle(cos(outerAngle))
    {
        constexpr int colorAttachmentsCount = Light::RSM_TEXTURES_COUNT - 1;

        GLuint attachments[colorAttachmentsCount] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};

        m_shadowmap.Bind();
        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap", GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT), GL_DEPTH_ATTACHMENT);

        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap_position", GL_RGB32F, GL_RGB, GL_FLOAT), attachments[0]);
        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap_normal", GL_RGB32F, GL_RGB, GL_FLOAT), attachments[1]);
        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap_flux", GL_RGB32F, GL_RGB, GL_FLOAT), attachments[2]);

        glDrawBuffers(colorAttachmentsCount, attachments);

        auto* texture = m_shadowmap.GetTexture(0);

        texture->Bind();
        texture->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        texture->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        texture->SetParameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        texture->Unbind();

        for (int i = 1; i < colorAttachmentsCount + 1; ++i)
        {
            m_shadowmap.GetTexture(i)->Bind();
            m_shadowmap.GetTexture(i)->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            m_shadowmap.GetTexture(i)->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            m_shadowmap.GetTexture(i)->Unbind();
        }

        m_shadowmap.Resize(1500, 1500);

        GIR_ASSERT(m_shadowmap.IsComplete(), "Incomplete spotlight framebuffer");

        m_shadowmap.Unbind();
    }

    void SpotLight::SetUniforms(const std::string &name, Shader *shader, int slot, bool bindTextures)
    {
        Light::SetUniforms(name, shader, slot, bindTextures);
        shader->SetUniform(name + ".type", static_cast<unsigned>(2));
        shader->SetUniform(name + ".position", Vec3f(m_transform[3]));
        shader->SetUniform(name + ".direction", Vec3f(-m_transform[2]));
        shader->SetUniform(name + ".cosInnerAngle", m_cosInnerAngle);
        shader->SetUniform(name + ".cosOuterAngle", m_cosOuterAngle);

        if (bindTextures)
        {
            shader->SetUniform(name + ".depthSM", slot);
            shader->SetUniform(name + ".positionSM", slot + 1);
            shader->SetUniform(name + ".normalSM", slot + 2);
            shader->SetUniform(name + ".fluxSM", slot + 3);
            shader->SetUniform(name + ".viewProjection", m_projection * GetView());
        }
    }

    const Mat4f &SpotLight::GetProjection() { return m_projection; }
} // namespace gir