#include "Camera.hpp"

namespace gir
{
    Camera::Camera(const Mat4f &transform, int width, int height, float vfov) :
        SceneComponent {transform},
        m_vfov {vfov},
        m_width {width},
        m_height {height}
    {
        m_projection = perspective(hfov, static_cast<float>(m_width) / m_height, nearZ, farZ);
    }

    void Camera::SetWidth(int width);

    void Camera::SetHeight(int height);

    void Camera::SetVerticalFOV(float vfov);

    const Mat4f &Camera::GetViewMatrix() const;

    const Mat4f &Camera::GetProjectionMatrix() const;

} // namespace gir