#include "Scene.hpp"

namespace gir
{
    Scene::Scene(const Camera &camera, std::vector<Light> &&lights, std::vector<Entity> &&entities) :
        m_renderSystem {*this},
        m_camera {camera},
        m_lights {std::move(lights)},
        m_entities {std::move(entities)}
    {
    }

    void draw() { m_renderSystem.draw(); }

    const Camera &Scene::GetCamera() const { return m_camera; }

    const std::vector<Light> &Scene::GetLights() const { return m_lights; }

    const std::vector<Entity> &Scene::GetEntities() const { return m_entities; }

} // namespace gir