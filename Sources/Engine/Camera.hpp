#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "SceneComponent.hpp"

#include <Core/Core.hpp>

namespace gir
{
    class Camera : public SceneComponent
    {
    public:
        Camera(const Mat4f &transform, int width, int height, float vfov = PI / 3);

        ~Camera() = default;

        void SetWidth(int width);

        void SetHeight(int height);

        void SetVerticalFOV(float vfov);

        const Mat4f &GetViewMatrix() const;

        const Mat4f &GetProjectionMatrix() const;

    private:
        Mat4f m_projection;

        float m_vfov;

        int m_width;

        int m_height;

        bool m_dirtyProj = false;

        static float nearZ = 0.5f;
        static float farZ  = 200.f;

        void updateProjection();
    };
} // namespace gir

#endif