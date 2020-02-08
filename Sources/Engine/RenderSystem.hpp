#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "Framebuffer.hpp"
#include "Scene.hpp"

namespace gir
{
    enum class RenderMode
    {
        DEBUG,
        RSM
    };

    // TODO: do
    class RenderSystem
    {
    public:
        RenderSystem(const Scene& scene);

        void draw();

        void ReloadShaders();

        void SetRenderMode(RenderMode mode);

    private:
        const Scene& m_scene;

        ShaderManager m_shaderManager;

        Framebuffer m_GBuffer;

        RenderMode mode;
    };

} // namespace gir

#endif