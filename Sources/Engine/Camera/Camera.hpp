#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/SceneComponent.hpp>

namespace gir
{
    class Camera : public SceneComponent
    {
    public:
        static float farZ;
        static float nearZ;

    public:
        Camera(const std::string &name, const Mat4f &transform, unsigned width, unsigned height, float vfov = PI / 3);

        ~Camera() override = default;

        inline void SetTransform(const Mat4f &transform) { m_transform = transform; }

        inline unsigned GetWidth() const { return m_width; }

        inline unsigned GetHeight() const { return m_height; }

        inline float GetVerticalFOV() const { return m_vfov; }

        inline float GetHorizontalFOV() const { return m_vfov * m_width / m_height; }

        void SetWidth(unsigned width);

        void SetHeight(unsigned height);

        void SetVerticalFOV(float vfov);

        Mat4f GetViewMatrix() const;

        const Mat4f &GetProjectionMatrix() const;

        const Mat4f &GetInverseProjection() const;

    private:
        void UpdateProjection() const;

    private:
        mutable Mat4f m_projection;
        
        mutable Mat4f m_inverseProjection;

        mutable bool m_isProjectionDirty = false;

        float m_vfov;

        unsigned m_width;
        unsigned m_height;
    };
} // namespace gir