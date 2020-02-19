#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/SceneComponent.hpp>

namespace gir
{
    class Camera : public SceneComponent
    {
    public:
        /// The projection frustum near distance.
        static float nearZ;
        /// The projection frustum far distance.
        static float farZ;

    public:
        Camera(const std::string &name,
               const Mat4f &transform,
               unsigned width,
               unsigned height,
               float vfov = PI / 3);

        ~Camera() override = default;

        inline unsigned GetWidth() const { return m_width; }

        inline unsigned GetHeight() const { return m_height; }

        inline float GetVerticalFOV() const { return m_vfov; }

        inline float GetHorizontalFOV() const { return m_vfov * float(m_width) / float(m_height); }

        void SetVerticalFOV(float vfov);

        void SetWidth(unsigned width);

        void SetHeight(unsigned height);

        const Mat4f &GetProjectionMatrix() const;

        const Mat4f &GetInverseProjection() const;

        /// @return: the camera's view matrix.
        Mat4f GetViewMatrix() const;

    private:
        /// Compute the new projection matrix.
        void UpdateProjection() const;

    private:
        mutable Mat4f m_projection = Mat4f(1.0f);

        mutable Mat4f m_inverseProjection = Mat4f(1.0f);

        /// Check if the projection matrix needs to be recomputed.
        mutable bool m_isProjectionDirty = false;

        /// Vertical field of view / Zoom
        float m_vfov;

        /// Width resolution.
        unsigned m_width;

        /// Height resolution.
        unsigned m_height;
    };
} // namespace gir