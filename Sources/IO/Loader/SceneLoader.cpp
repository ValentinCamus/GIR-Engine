#include "SceneLoader.hpp"

#include <Engine/Light/DirectionalLight.hpp>
#include <Engine/Light/SpotLight.hpp>
#include <Engine/Light/PointLight.hpp>

#include <IO/Loader/ModelLoader.hpp>

#include <Engine/Manager/Manager.hpp>

namespace gir
{
    std::unique_ptr<Scene> SceneLoader::Load(const std::string &filepath)
    {
        Manager<Texture>::Clear();
        Manager<Material>::Clear();
        Manager<Mesh>::Clear();
        Manager<Model>::Clear();

        std::ifstream sceneFile(filepath);
        nlohmann::json jsonFile;
        sceneFile >> jsonFile;

        Camera camera = LoadCamera(jsonFile["Camera"]);
        std::vector<std::unique_ptr<Light>> lights = LoadLights(jsonFile["Lights"]);
        std::vector<std::unique_ptr<Entity>> entities = LoadEntities(jsonFile["Entities"]);

        return std::make_unique<Scene>(camera, std::move(lights), std::move(entities));
    }

    Camera SceneLoader::LoadCamera(nlohmann::json object)
    {
        std::string name = object["Name"].get<std::string>();

        Vec3f location {
            object["WorldLocation"]["X"].get<float>(),
            object["WorldLocation"]["Y"].get<float>(),
            object["WorldLocation"]["Z"].get<float>()
        };
        Vec3f rotation {
            object["WorldRotation"]["Pitch"].get<float>(),
            object["WorldRotation"]["Yaw"].get<float>(),
            object["WorldRotation"]["Roll"].get<float>()
        };

        auto width = object["Width"].get<unsigned>();
        auto height = object["Height"].get<unsigned>();

        Mat4f transform {1.0f};
        transform = glm::rotate(transform, glm::radians(rotation.x), {1.0f, 0.0f, 0.0f});
        transform = glm::rotate(transform, glm::radians(rotation.y), {0.0f, 1.0f, 0.0f});
        transform = glm::rotate(transform, glm::radians(rotation.z), {0.0f, 0.0f, 1.0f});
        transform[3] = Vec4f(location, 1.0f);

        return Camera(name, transform, width, height);
    }

    std::vector<std::unique_ptr<Light>> SceneLoader::LoadLights(nlohmann::json object)
    {
        std::vector<std::unique_ptr<Light>> lights;

        for (auto& item : object.items())
        {
            auto light = item.value();

            std::string name = light["Name"].get<std::string>();
            std::string type = light["Type"].get<std::string>();

            Vec3f location {
                light["WorldLocation"]["X"].get<float>(),
                light["WorldLocation"]["Y"].get<float>(),
                light["WorldLocation"]["Z"].get<float>()
            };
            Vec3f rotation {
                light["WorldRotation"]["Pitch"].get<float>(),
                light["WorldRotation"]["Yaw"].get<float>(),
                light["WorldRotation"]["Roll"].get<float>()
            };

            Mat4f transform {1.0f};
            transform = glm::rotate(transform, glm::radians(rotation.x), {1.0f, 0.0f, 0.0f});
            transform = glm::rotate(transform, glm::radians(rotation.y), {0.0f, 1.0f, 0.0f});
            transform = glm::rotate(transform, glm::radians(rotation.z), {0.0f, 0.0f, 1.0f});
            transform[3] = Vec4f(location, 1.0f);

            Vec3f color {
                light["Color"]["Red"].get<float>(),
                light["Color"]["Blue"].get<float>(),
                light["Color"]["Green"].get<float>()
            };

            if (type == "DirectionalLight")
            {
                Logger::Info("[DirectionalLight] {}: Loaded", name);

                lights.emplace_back(std::make_unique<DirectionalLight>(name, transform, color));
            }
            else if (type == "SpotLight")
            {
                Logger::Info("[SpotLight] {}: Loaded", name);

                auto innerAngle = glm::radians(light["InnerAngle"].get<float>());
                auto outerAngle = glm::radians(light["OuterAngle"].get<float>());

                lights.emplace_back(std::make_unique<SpotLight>(name, transform, color, innerAngle, outerAngle));
            }
            else if (type == "PointLight")
            {
                Logger::Info("[PointLight] {}: Loaded", name);

                lights.emplace_back(std::make_unique<PointLight>(name, transform, color));
            }
            else GIR_ASSERT(false, "SceneLoader::LoadLights: Invalid light type");
        }

        return lights;
    }

    std::vector<std::unique_ptr<Entity>> SceneLoader::LoadEntities(nlohmann::json object)
    {
        std::vector<std::unique_ptr<Entity>> entities;

        std::unordered_map<std::string, Model*> models;

        for (auto& item : object.items())
        {
            auto entity = item.value();

            std::string name = entity["Name"].get<std::string>();

            std::string file = entity["UseProjectSourceDirectory"].get<bool>()
                    ? FileSystem::GetProjectDir() + entity["Filename"].get<std::string>()
                    : entity["Filename"].get<std::string>();

            Model* model = nullptr;

            auto modelIterator = models.find(file);
            if (modelIterator != models.end())
            {
                model = modelIterator->second;
            }
            else
            {
                model = ModelLoader::Load(file);
                models.insert({file, model});
            }

            Vec3f location {
                entity["WorldLocation"]["X"].get<float>(),
                entity["WorldLocation"]["Y"].get<float>(),
                entity["WorldLocation"]["Z"].get<float>()
            };
            Vec3f rotation {
                entity["WorldRotation"]["Pitch"].get<float>(),
                entity["WorldRotation"]["Yaw"].get<float>(),
                entity["WorldRotation"]["Roll"].get<float>()
            };
            Vec3f scale {
                entity["WorldScale"]["X"].get<float>(),
                entity["WorldScale"]["Y"].get<float>(),
                entity["WorldScale"]["Z"].get<float>()
            };

            Mat4f transform {1.0f};
            transform = glm::scale(transform, scale);
            transform = glm::rotate(transform, glm::radians(rotation.x), {1.0f, 0.0f, 0.0f});
            transform = glm::rotate(transform, glm::radians(rotation.y), {0.0f, 1.0f, 0.0f});
            transform = glm::rotate(transform, glm::radians(rotation.z), {0.0f, 0.0f, 1.0f});
            transform[3] = Vec4f(location, 1.0f);

            entities.emplace_back(std::make_unique<Entity>(name, model, transform));
        }

        return entities;
    }
}