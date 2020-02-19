#pragma once

#include <Core/Core.hpp>

#include <Engine/Camera/Camera.hpp>

namespace gir
{
    class CameraController
    {
    public:
        explicit CameraController(Camera* camera);

        /// Move the controlled camera forward.
        void MoveForward(float deltaTime);

        /// Move the controlled camera backward.
        void MoveBackward(float deltaTime);

        /// Move the controlled camera right.
        void MoveRight(float deltaTime);

        /// Move the controlled camera left.
        void MoveLeft(float deltaTime);

        /// Move the controlled camera up.
        void MoveUp(float deltaTime);

        /// Move the controlled camera down.
        void MoveDown(float deltaTime);

        /// Zoom/Un-zoom the camera.
        void Zoom(float delta);

        void DragMouse(float xPos, float yPos);

        void SetMousePosition(float x, float y);

        inline const Camera* GetCamera() const { return m_camera; }

        inline void SetCamera(Camera* camera) { m_camera = camera; }

    private:
        /// Controlled camera.
        Camera* m_camera;

        /// Camera speed.
        float m_speed = 5.5f;

        float m_zoomSensitivity = 2.0f;
        float m_minZoom = 0.1f * DEG2RAD;
        float m_maxZoom = 90.0f * DEG2RAD;

        float m_prevMouseX = 0.f;
        float m_prevMouseY = 0.f;

        // bool m_mouseDragged = false;
    };
} // namespace gir