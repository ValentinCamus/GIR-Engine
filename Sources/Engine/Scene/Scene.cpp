#include "Scene.hpp"

namespace gir
{
    Scene::Scene(const Camera &camera, std::vector<Light> &&lights, std::vector<Entity> &&entities) :
        m_camera {camera},
        m_lights {std::move(lights)},
        m_entities {std::move(entities)}
    {

    }

} // namespace gir