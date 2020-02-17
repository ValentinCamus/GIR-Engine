#pragma once

#include <Core/Core.hpp>
#include "Engine/Camera/Camera.hpp"
#include "Engine/Mesh/Entity.hpp"
#include "Engine/Light/Light.hpp"

namespace gir
{
    class Scene
    {
    public:
        Scene(const Camera &camera,
              std::vector<std::unique_ptr<Light>> &&lights,
              std::vector<std::unique_ptr<Entity>> &&entities);

        ~Scene() = default;

        inline Camera &GetCamera() { return m_camera; }

        inline const Camera &GetCamera() const { return m_camera; }

        inline const std::vector<std::unique_ptr<Light>> &GetLights() const { return m_lights; }

        inline const std::vector<std::unique_ptr<Entity>> &GetEntities() const { return m_entities; }

    private:
        Camera m_camera;

        std::vector<std::unique_ptr<Light>> m_lights;
        std::vector<std::unique_ptr<Entity>> m_entities;
    };
} // namespace gir