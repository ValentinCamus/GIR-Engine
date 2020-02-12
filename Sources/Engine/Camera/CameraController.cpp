#include "CameraController.hpp"

namespace gir
{
    CameraController::CameraController(Camera *camera) : m_camera(camera) {}

    void CameraController::MoveForward(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;

        Mat4f transform(m_camera->GetTransform());
        const Vec3f &forward = transform[2];

        transform[3] += Vec4f(forward * velocity, 0.f);

        m_camera->SetTransform(transform);
    }

    void CameraController::MoveBackward(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;

        Mat4f transform(m_camera->GetTransform());
        const Vec3f &backward = -transform[2];

        transform[3] += Vec4f(backward * velocity, 0.f);

        m_camera->SetTransform(transform);
    }

    void CameraController::MoveRight(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;

        Mat4f transform(m_camera->GetTransform());
        const Vec3f &right = -transform[0];

        transform[3] += Vec4f(right * velocity, 0.f);

        m_camera->SetTransform(transform);
    }

    void CameraController::MoveLeft(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;

        Mat4f transform(m_camera->GetTransform());
        const Vec3f &left = transform[0];

        transform[3] += Vec4f(left * velocity, 0.f);

        m_camera->SetTransform(transform);
    }

    void CameraController::MoveUp(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;

        Mat4f transform(m_camera->GetTransform());
        const Vec3f &up = -transform[1];

        transform[3] += Vec4f(up * velocity, 0.f);

        m_camera->SetTransform(transform);
    }

    void CameraController::MoveDown(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;

        Mat4f transform(m_camera->GetTransform());
        const Vec3f &down = transform[1];

        transform[3] += Vec4f(down * velocity, 0.f);

        m_camera->SetTransform(transform);
    }

    void CameraController::Zoom(float delta)
    {
        if (!m_camera) return;

        float zoom = m_camera->GetVerticalFOV() - delta * m_zoomSensitivity * DEG2RAD;

        m_camera->SetVerticalFOV(Clamp(zoom, m_minZoom, m_maxZoom));
    }

    void CameraController::LookAt(float xPos, float yPos)
    {
        if (!m_camera) return;

        const Mat4f &transform(m_camera->GetTransform());
        unsigned width  = m_camera->GetWidth();
        unsigned height = m_camera->GetHeight();

        float x = xPos - m_xPrev + width / 2;
        float y = yPos - m_yPrev + height / 2;

        m_xPrev = xPos;
        m_yPrev = yPos;

        // Map x and y to [-1, 1]
        Vec4f front(1 - 2 * x / width, 2 * y / height - 1, 0.f, 1.f);

        front = m_camera->GetInverseProjection() * front;
        front /= front.w;
        front.w = 0;
        front   = transform * glm::normalize(front);

        Vec4f right(glm::normalize(glm::cross(Vec3f(front), Vec3f(0.f, 1.f, 0.f))), 0.f);

        Vec4f up(glm::cross(Vec3f(right), Vec3f(front)), 0.f);

        m_camera->SetTransform({right, up, -front, transform[3]});
    }

    void CameraController::SetMousePos(float x, float y)
    {
        m_xPrev = x;
        m_yPrev = y;
    }
} // namespace gir