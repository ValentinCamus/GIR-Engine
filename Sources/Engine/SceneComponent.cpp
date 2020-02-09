#include "SceneComponent.hpp"

namespace gir
{
    SceneComponent::SceneComponent(const Mat4f& transform = Mat4f {1.f}) : m_transform {transform} {}

    const Mat4f& SceneComponent::GetTransform() const { return m_transform; }

} // namespace gir