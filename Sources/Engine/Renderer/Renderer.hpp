#pragma once

#include <Core/Core.hpp>
#include <Engine/Shader/ShaderManager.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

namespace gir
{
    enum class ERenderMode
    {
        DEBUG  = 0,
        DIRECT = 1,
        RSM    = 2,
        RSMGS  = 3
    };

    class Scene;
    class Mesh;

    class Renderer
    {
    public:
        Renderer(unsigned width, unsigned height);

        void Draw(Framebuffer* framebuffer, const Scene *scene);

        void ResizeGBuffer(unsigned width, unsigned height);

        void SetRenderMode(ERenderMode mode);

    private:
        ShaderManager m_shaderManager;

        Framebuffer m_GBuffer;

        std::unique_ptr<Mesh> m_quad = nullptr;

        ERenderMode m_renderMode = ERenderMode::DIRECT;
    };

} // namespace gir