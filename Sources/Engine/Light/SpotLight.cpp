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
        m_outerAngle(outerAngle)
    {
    }

    void SpotLight::SetUniforms(const std::string &name, Shader *shader)
    {
        Light::SetUniforms(name, shader);
        shader->SetUniform(name + ".type", static_cast<unsigned>(2));
        shader->SetUniform(name + ".position", Vec3f(m_transform[3]));
        shader->SetUniform(name + ".direction", Vec3f(-m_transform[2]));
        shader->SetUniform(name + ".innerAngle", m_innerAngle);
        shader->SetUniform(name + ".outerAngle", m_outerAngle);
    }

    const Mat4f &SpotLight::GetProjection() const { return m_projection; }
} // namespace gir