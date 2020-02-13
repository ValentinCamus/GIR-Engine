#pragma once

#include <Core/Core.hpp>
#include <Engine/Scene/Scene.hpp>
#include <Engine/Shader/ShaderManager.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

namespace gir
{
    enum class ERenderMode
    {
        DEBUG,
        RSM
    };

    constexpr unsigned GBUFFER_ATTACHMENTS[4] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };

    class Renderer
    {
    public:
        Renderer(unsigned width, unsigned height);

        /// @scene: The scene to render.
        /// @framebuffer: Where to draw the scene.
        void Draw(const Scene *scene, Framebuffer* framebuffer = nullptr);

        inline void ResizeGBuffer(unsigned width, unsigned height) { m_GBuffer.Resize(width, height); }

        inline ERenderMode GetRenderMode() const { return m_renderMode; }

        inline void SetRenderMode(ERenderMode mode) { m_renderMode = mode; }

    private:
        void InitializeGBuffer(unsigned width, unsigned height);

        void GBufferDraw(const Scene *scene);

    private:
        ShaderManager m_shaderManager;

        Framebuffer m_GBuffer;

        std::unique_ptr<Mesh> m_quad = nullptr;

        ERenderMode m_renderMode = ERenderMode::DEBUG;
    };

} // namespace gir