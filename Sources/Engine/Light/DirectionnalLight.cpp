#include "DirectionnalLight.hpp"

namespace gir
{
    const Mat4f DirectionnalLight::m_projection = glm::ortho(-50.f, 50.f, -50.f, 15.f, NEAR_Z, FAR_Z);

    DirectionnalLight::DirectionnalLight(const std::string &name, const Mat4f &transform, const Vec3f &color) :
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

        GIR_ASSERT(m_shadowmap.IsComplete(), "Incomplete directionnal light framebuffer");

        m_shadowmap.Unbind();
    }

    void DirectionnalLight::SetUniforms(const std::string &name, Shader *shader, int slot, bool bindTextures)
    {
        Light::SetUniforms(name, shader, slot);
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

    const Mat4f &DirectionnalLight::GetProjection() { return m_projection; }
} // namespace gir