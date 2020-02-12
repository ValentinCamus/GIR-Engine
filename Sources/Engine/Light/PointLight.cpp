#include "PointLight.hpp"

namespace gir
{
    const Mat4f PointLight::m_projection = glm::perspective(PI / 2, 1.f, NEAR_Z, FAR_Z);

    PointLight::PointLight(const std::string& name, const Mat4f& transform, const Vec3f& color) :
        Light(name, transform, color)
    {
    }

    void PointLight::SetUniforms(const std::string& name, Shader* shader)
    {
        Light::SetUniforms(name, shader);
        shader->SetUniform(name + ".type", 0);
    }

    const Mat4f& PointLight::GetProjection() const { return m_projection; }
} // namespace gir