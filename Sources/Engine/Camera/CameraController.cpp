#include "CameraController.hpp"

namespace gir
{
    CameraController::CameraController(Camera *camera)
        : m_camera(camera)
    {

    }

    void CameraController::MoveForward(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;
        const Vec3f &forward = m_camera->GetTransform()[2];

        m_camera->SetTransform(glm::translate(m_camera->GetTransform(), forward * velocity));
    }

    void CameraController::MoveBackward(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;
        const Vec3f &forward = m_camera->GetTransform()[2];

        m_camera->SetTransform(glm::translate(m_camera->GetTransform(), -forward * velocity));
    }

    void CameraController::MoveRight(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;
        const Vec3f &right = m_camera->GetTransform()[0];

        m_camera->SetTransform(glm::translate(m_camera->GetTransform(), -right * velocity));
    }

    void CameraController::MoveLeft(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;
        const Vec3f &right = m_camera->GetTransform()[0];

        m_camera->SetTransform(glm::translate(m_camera->GetTransform(), right * velocity));
    }

    void CameraController::MoveUp(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;
        const Vec3f &up = m_camera->GetTransform()[1];

        m_camera->SetTransform(glm::translate(m_camera->GetTransform(), up * velocity));
    }

    void CameraController::MoveDown(float deltaTime)
    {
        if (!m_camera) return;

        float velocity = m_speed * deltaTime;
        const Vec3f &up = m_camera->GetTransform()[1];

        m_camera->SetTransform(glm::translate(m_camera->GetTransform(), -up * velocity));
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

        // TODO
    }
}