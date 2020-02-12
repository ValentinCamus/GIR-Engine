#include "Light.hpp"

namespace gir
{
    Light::Light(const std::string &name, const Mat4f &transform, const Vec3f &color) :
        SceneComponent(name, transform),
        m_color(color)
    {
    }

    Mat4f Light::GetView() const
    {
        Mat4f view;

        const Vec3f &translation = m_transform[3];
        const Mat3f &rotation    = m_transform;

        view       = transpose(rotation);
        view[3][0] = -dot(translation, rotation[0]);
        view[3][1] = -dot(translation, rotation[1]);
        view[3][2] = -dot(translation, rotation[2]);
        view[3][3] = 1.f;
        return view;
    }

    void Light::SetUniforms(const std::string &name, Shader *shader)
    {
        shader->SetUniform(name + ".color", m_color);
    }
} // namespace gir