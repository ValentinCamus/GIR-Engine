#pragma once

#include <Core/Core.hpp>

#include <Engine/Scene/Scene.hpp>

#include <nlohmann/json.hpp>

namespace gir
{
    class SceneLoader
    {
    public:
        static std::unique_ptr<Scene> Load(const std::string& filepath);

    private:
        static Camera LoadCamera(nlohmann::json object);

        static std::vector<std::unique_ptr<Light>> LoadLights(nlohmann::json object);

        static std::vector<std::unique_ptr<Entity>> LoadEntities(nlohmann::json object);
    };
}



