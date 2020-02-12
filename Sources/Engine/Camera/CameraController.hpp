#pragma once

#include <Core/Core.hpp>

#include <Engine/Camera/Camera.hpp>

namespace gir
{
    class CameraController
    {
    public:
        explicit CameraController(Camera* camera);

        void MoveForward(float deltaTime);

        void MoveBackward(float deltaTime);

        void MoveRight(float deltaTime);

        void MoveLeft(float deltaTime);

        void MoveUp(float deltaTime);

        void MoveDown(float deltaTime);

        void Zoom(float delta);

        void LookAt(float xPos, float yPos);

        void SetMousePos(float x, float y);

        inline const Camera* GetCamera() const { return m_camera; }

        inline void SetCamera(Camera* camera) { m_camera = camera; }

    private:
        Camera* m_camera;

        float m_speed = 2.5f;

        // float m_mouseSensitivity = 0.1f;

        float m_zoomSensitivity = 2.0f;
        float m_minZoom         = 0.1f * DEG2RAD;
        float m_maxZoom         = 90.0f * DEG2RAD;

        float m_xPrev = 0.f;
        float m_yPrev = 0.f;
    };
} // namespace gir