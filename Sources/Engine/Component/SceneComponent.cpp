#include "SceneComponent.hpp"

namespace gir
{
    SceneComponent::SceneComponent(const std::string& name, const Mat4f& transform) :
        Component {name},
        m_transform {transform}
    {

    }

} // namespace gir