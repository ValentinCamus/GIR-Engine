#pragma once

#include <Core/Core.hpp>
#include "Engine/Camera/Camera.hpp"
#include "Engine/Mesh/Entity.hpp"

namespace gir
{
    class Light;

    class Scene
    {
    public:
        Scene(const Camera &camera, std::vector<Light *> &&lights, std::vector<Entity> &&entities);

        ~Scene() = default;

        inline Camera &GetCamera() { return m_camera; }

        inline const Camera &GetCamera() const { return m_camera; }

        inline const std::vector<Light *> &GetLights() const { return m_lights; }

        inline const std::vector<Entity> &GetEntities() const { return m_entities; }

    private:
        Camera m_camera;

        std::vector<Light *> m_lights;

        std::vector<Entity> m_entities;
    };
} // namespace gir