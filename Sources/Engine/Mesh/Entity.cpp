#include "Entity.hpp"

namespace gir
{
    Entity::Entity(const std::string& name, Model* model, const Mat4f& transform) :
        SceneComponent(name, transform),
        m_model(model)
    {

    }

} // namespace gir