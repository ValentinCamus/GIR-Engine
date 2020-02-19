#include "DirectionalLight.hpp"

namespace gir
{
    const Mat4f DirectionalLight::m_projection = glm::ortho(-50.f, 50.f, -50.f, 15.f, NEAR_Z, FAR_Z);

    DirectionalLight::DirectionalLight(const std::string &name, const Mat4f &transform, const Vec3f &color) :
            Light(name, transform, color)
    {
        m_shadowmap.Bind();
        m_shadowmap.AttachTexture(std::make_unique<Texture>(name + "_shadowmap", GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT),
                                  GL_DEPTH_ATTACHMENT);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        auto *texture = m_shadowmap.GetTexture(0);

        texture->Bind();
        texture->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        texture->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        texture->SetParameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        texture->Unbind();

        m_shadowmap.Resize(4850, 3200);

        GIR_ASSERT(m_shadowmap.IsComplete(), "Incomplete directional light framebuffer");

        m_shadowmap.Unbind();
    }

    void DirectionalLight::SetUniforms(const std::string &name, Shader *shader, int slot)
    {
        Light::SetUniforms(name, shader, slot);
        shader->SetUniform(name + ".type", static_cast<unsigned>(1));
        shader->SetUniform(name + ".direction", Vec3f(-m_transform[2]));

        shader->SetUniform(name + ".shadowmap", slot);
        shader->SetUniform(name + ".viewProjection", m_projection * GetView());
    }

    const Mat4f &DirectionalLight::GetProjection() { return m_projection; }
} // namespace gir