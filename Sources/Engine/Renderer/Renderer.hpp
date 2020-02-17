#pragma once

#include <Core/Core.hpp>
#include <Engine/OpenGL/OpenGL.hpp>
#include <Engine/Renderer/Quad.hpp>
#include <Engine/Shader/ShaderManager.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>
#include <Engine/Scene/Scene.hpp>
#include <Engine/Camera/Camera.hpp>

namespace gir
{
    enum class ERenderMode
    {
        UNLIT  = 0,
        DIRECT = 1,
        RSM    = 2,
        RSMGS  = 3
    };

    class Renderer
    {
    public:
        Renderer(unsigned width, unsigned height);

        void Draw(Framebuffer* framebuffer, const Scene* scene);

        void DrawTexture(Texture2D* texture, const Camera& camera, Framebuffer* framebuffer);

        inline void ResizeGBuffer(unsigned width, unsigned height) { m_GBuffer.Resize(width, height); }

        inline void SetRenderMode(ERenderMode mode) { m_renderMode = mode; }

    private:
        static ShaderManager GetDefaultShaderManager();

        void InitializeGBuffer(unsigned width, unsigned height);

        void DrawGBuffer(const Scene* scene);

    private:
        ShaderManager m_shaderManager;

        Framebuffer m_GBuffer;

        std::unique_ptr<Quad> m_quad = nullptr;

        ERenderMode m_renderMode = ERenderMode::DIRECT;
    };

} // namespace gir