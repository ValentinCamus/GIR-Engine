#pragma once

#include <Core/Core.hpp>
#include "Engine/Scene/Scene.hpp"
#include <Engine/Shader/ShaderManager.hpp>
#include "Engine/Framebuffer/Framebuffer.hpp"

namespace gir
{
    enum class RenderMode
    {
        DEBUG,
        RSM
    };

    class Renderer
    {
    public:
        Renderer(const Scene& scene);

        void Draw();

        void ReloadShaders();

        void SetRenderMode(RenderMode mode);

    private:
        const Scene& m_scene;

        ShaderManager m_shaderManager;

        Framebuffer m_gBuffer;

        RenderMode m_renderMode = RenderMode::DEBUG;
    };

} // namespace gir