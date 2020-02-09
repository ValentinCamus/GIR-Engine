#include "Entity.hpp"

namespace gir
{
    Entity::Entity(const std::string& name, const Mat4f& transform = Mat4f {1.f}, const Model& model) :
        SceneComponent {name, transform},
        m_model {model}
    {
    }

    const Model& Entity::model() const { return m_model; }
} // namespace gir