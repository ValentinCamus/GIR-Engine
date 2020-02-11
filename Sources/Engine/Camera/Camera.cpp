#include "Camera.hpp"

namespace gir
{
    float Camera::nearZ = 0.5f;
    float Camera::farZ  = 200.0f;

    Camera::Camera(const std::string &name, const Mat4f &transform, unsigned width, unsigned height, float vfov) :
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
        m_width             = width;
    }

    void Camera::SetHeight(unsigned height)
    {
        m_isProjectionDirty = true;
        m_height            = height;
    }

    void Camera::SetVerticalFOV(float vfov)
    {
        m_isProjectionDirty = true;
        m_vfov              = vfov;
    }

    const Mat4f &Camera::GetViewMatrix()
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

    const Mat4f &Camera::GetProjectionMatrix()
    {
        if (m_isProjectionDirty) UpdateProjection();

        // TODO:
        return m_projection;
    }

    void Camera::UpdateProjection()
    {
        m_projection = glm::perspective(m_vfov, static_cast<float>(m_width) / m_height, nearZ, farZ);

        m_isProjectionDirty = false;
    }

} // namespace gir