#include "PointLight.hpp"

namespace gir
{
    const Mat4f PointLight::m_projection = glm::perspective(PI / 2, 1.f, NEAR_Z, FAR_Z);

    PointLight::PointLight(const std::string& name, const Mat4f& transform, const Vec3f& color) :
        Light(name, transform, color)
    {
    }

    void PointLight::SetUniforms(const std::string& name, Shader* shader, int slot)
    {
        Light::SetUniforms(name, shader, slot);
        shader->SetUniform(name + ".type", static_cast<unsigned>(0));
        shader->SetUniform(name + ".position", Vec3f(m_transform[3]));

        shader->SetUniform(name + ".shadowmapPL", slot);
    }

    const Mat4f& PointLight::GetProjection() { return m_projection; }
} // namespace gir