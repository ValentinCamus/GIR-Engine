#ifndef SCENECOMPONENT_HPP
#define SCENECOMPONENT_HPP

#include "Component.hpp"
#include <Core/Types.hpp>

namespace gir
{
    class SceneComponent : public Component
    {
    public:
        SceneComponent(const std::string& name, const Mat4f& transform = Mat4f {1.f});

        ~SceneComponent() = default;

        const Mat4f& GetTransform() const;

        // void Scale();

    private:
        Mat4f m_transform;
    };
} // namespace gir

#endif