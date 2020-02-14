#pragma once

#include <Core/Core.hpp>
#include <Engine/Shader/ShaderManager.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

namespace gir
{
    enum class RenderMode
    {
        DEBUG,
        RSM
    };

    class Scene;
    class Mesh;

    class Renderer
    {
    public:
        Renderer(Framebuffer *defaultFramebuffer, unsigned width, unsigned height);

        void Draw(const Scene *scene);

        void ResizeGBuffer(unsigned width, unsigned height);

        void SetRenderMode(RenderMode mode);

    private:
        ShaderManager m_shaderManager;

        Framebuffer *m_defaultFramebuffer;

        Framebuffer m_GBuffer;

        std::unique_ptr<Mesh> m_quad = nullptr;

        RenderMode m_renderMode = RenderMode::RSM;
    };

} // namespace gir