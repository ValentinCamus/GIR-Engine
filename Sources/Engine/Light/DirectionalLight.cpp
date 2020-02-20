#include "DirectionalLight.hpp"

namespace gir
{
    const Mat4f DirectionalLight::m_projection = glm::ortho(-25.f, 25.f, -20.f, 5.f, NEAR_Z, FAR_Z);

    DirectionalLight::DirectionalLight(const std::string &name, const Mat4f &transform, const Vec3f &color) :
            Light(name, transform, color)
    {
        constexpr int colorAttachmentsCount = Light::RSM_TEXTURES_COUNT - 1;

        GLuint attachments[colorAttachmentsCount] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};

        m_shadowmap.Bind();
        m_shadowmap.AttachTexture(
            std::make_unique<Texture>(name + "_shadowmap", GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT),
            GL_DEPTH_ATTACHMENT);

        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap_position", GL_RGB32F, GL_RGB, GL_FLOAT),
                                  attachments[0]);
        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap_normal", GL_RGB32F, GL_RGB, GL_FLOAT),
                                  attachments[1]);
        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap_flux", GL_RGB32F, GL_RGB, GL_FLOAT),
                                  attachments[2]);

        glDrawBuffers(colorAttachmentsCount, attachments);

        auto *texture = m_shadowmap.GetTexture(0);

        texture->Bind();
        texture->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        texture->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        texture->SetParameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        texture->Unbind();

        for (int i = 1; i < colorAttachmentsCount + 1; ++i)
        {
            texture = m_shadowmap.GetTexture(i);
            texture->Bind();
            texture->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            texture->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            texture->Unbind();
        }

        m_shadowmap.Resize(4000, 2800);

        GIR_ASSERT(m_shadowmap.IsComplete(), "Incomplete directional light framebuffer");

        m_shadowmap.Unbind();
    }

    void DirectionalLight::SetUniforms(const std::string &name, Shader *shader, int slot, bool bindTextures)
    {
        Light::SetUniforms(name, shader, slot, bindTextures);
        shader->SetUniform(name + ".type", static_cast<unsigned>(1));
        shader->SetUniform(name + ".direction", Vec3f(-m_transform[2]));

        if (bindTextures)
        {
            shader->SetUniform(name + ".depthSM", slot);
            shader->SetUniform(name + ".positionSM", slot + 1);
            shader->SetUniform(name + ".normalSM", slot + 2);
            shader->SetUniform(name + ".fluxSM", slot + 3);
            shader->SetUniform(name + ".viewProjection", m_projection * GetView());
        }
    }

    const Mat4f &DirectionalLight::GetProjection()
    {
        return m_projection;
    }
} // namespace gir