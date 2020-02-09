#ifndef SCENE_HPP
#define SCENE_HPP

#include <Core/Core.hpp>
#include "RenderSystem.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Entity.hpp"

namespace gir
{
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