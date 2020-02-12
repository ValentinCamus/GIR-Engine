#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    class SceneComponent : public Component
    {
    public:
        explicit SceneComponent(const std::string& name, const Mat4f& transform = Mat4f {1.f});

        ~SceneComponent() override = default;

        inline const Mat4f& GetTransform() const { return m_transform; }

        inline void SetTransform(const Mat4f& transform) { m_transform = transform; }

    protected:
        Mat4f m_transform;
    };
} // namespace gir
