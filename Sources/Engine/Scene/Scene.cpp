#include "Scene.hpp"

namespace gir
{
    Scene::Scene(const Camera &camera,
                 std::vector<std::unique_ptr<Light>> &&lights,
                 std::vector<std::unique_ptr<Entity>> &&entities) :
        m_camera(camera),
        m_lights(std::move(lights)),
        m_entities(std::move(entities))
    {
    }

} // namespace gir