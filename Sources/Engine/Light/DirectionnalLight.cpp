#include "DirectionnalLight.hpp"

namespace gir
{
    const Mat4f DirectionnalLight::m_projection = glm::ortho(-85.f, 85.f, -85.f, 100.f, NEAR_Z, FAR_Z);

    DirectionnalLight::DirectionnalLight(const std::string &name, const Mat4f &transform, const Vec3f &color) :
        Light(name, transform, color)
    {
    }

    void DirectionnalLight::SetUniforms(const std::string &name, Shader *shader)
    {
        Light::SetUniforms(name, shader);
        shader->SetUniform(name + ".type", 1);
        shader->SetUniform(name + ".direction", Vec3f(-m_transform[2]));
    }

    const Mat4f &DirectionnalLight::GetProjection() const { return m_projection; }
} // namespace gir