#include "Camera.hpp"

namespace gir
{
    float Camera::nearZ = 0.1f;
    float Camera::farZ  = 100.0f;

    Camera::Camera(const std::string &name,
                   const Mat4f &transform,
                   unsigned width,
                   unsigned height,
                   float vfov) :
        SceneComponent(name, transform),
        m_vfov(vfov),
        m_width(width),
        m_height(height)
    {
        UpdateProjection();
    }

    void Camera::SetWidth(unsigned width)
    {
        m_isProjectionDirty = true;

        m_width = width;
    }

    void Camera::SetHeight(unsigned height)
    {
        m_isProjectionDirty = true;

        m_height = height;
    }

    void Camera::SetVerticalFOV(float vfov)
    {
        m_isProjectionDirty = true;

        m_vfov = vfov;
    }

    Mat4f Camera::GetViewMatrix() const
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

    const Mat4f &Camera::GetProjectionMatrix() const
    {
        if (m_isProjectionDirty) UpdateProjection();

        return m_projection;
    }

    void Camera::UpdateProjection() const
    {
        m_isProjectionDirty = false;

        m_projection = glm::perspective(m_vfov, float(m_width) / float(m_height), nearZ, farZ);
    }

} // namespace gir