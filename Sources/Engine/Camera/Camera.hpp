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

        inline unsigned GetWidth() const { return m_width; }

        inline unsigned GetHeight() const { return m_height; }

        inline float GetVerticalFOW() const { return m_vfov; }

        void SetWidth(unsigned width);

        void SetHeight(unsigned height);

        void SetVerticalFOV(float vfov);

        Mat4f GetViewMatrix() const;

        const Mat4f &GetProjectionMatrix() const;

    private:
        void UpdateProjection() const;

    private:
        mutable Mat4f m_projection;

        mutable bool m_isProjectionDirty = false;

        float m_vfov;

        unsigned m_width;
        unsigned m_height;
    };

} // namespace gir