#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

namespace gir
{
    class Light;
    class Entity;
    class Camera;

    // TODO: do
    class Scene
    {
    public:
        Scene()  = default;
        ~Scene() = default;

        const Camera &camera() const;

        const std::vector<Light> &lights() const;

        const std::vector<Entity> &entities() const;

    private:
        Camera m_camera;

        std::vector<Light> m_lights;

        std::vector<Entity> m_entities;
    };

} // namespace gir

#endif