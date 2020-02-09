#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include <RenderSystem.hpp>

namespace gir
{
    class Light;
    class Entity;
    class Camera;

    // TODO: do
    class Scene
    {
    public:
        Scene(const Camera &camera, std::vector<Light> &&lights, std::vector<Entity> &&entities);
        ~Scene() = default;

        void draw();

        const Camera &GetCamera() const;

        const std::vector<Light> &GetLights() const;

        const std::vector<Entity> &GetEntities() const;

    private:
        RenderSystem m_renderSystem;

        Camera m_camera;

        std::vector<Light> m_lights;

        std::vector<Entity> m_entities;
    };

} // namespace gir

#endif