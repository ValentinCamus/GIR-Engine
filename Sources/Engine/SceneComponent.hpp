#ifndef SCENECOMPONENT_HPP
#define SCENECOMPONENT_HPP

#include <Core/Types.hpp>

namespace gir
{
    class SceneComponent
    {
    public:
        SceneComponent(const Mat4f& transform = Mat4f {1.f});

        const Mat4f& GetTransform() const;

        // void Scale();

    private:
        Mat4f m_transform;
    };
} // namespace gir

#endif