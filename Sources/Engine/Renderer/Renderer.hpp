#pragma once

#include <Core/Core.hpp>
#include <Engine/Shader/ShaderManager.hpp>
#include "Engine/Framebuffer/Framebuffer.hpp"

namespace gir
{
    enum class RenderMode
    {
        DEBUG,
        RSM
    };

    class Scene;

    class Renderer
    {
    public:
        Renderer();

        void Draw(const Scene *scene);

        void SetRenderMode(RenderMode mode);

    private:
        ShaderManager m_shaderManager;

        Framebuffer m_gBuffer;

        RenderMode m_renderMode = RenderMode::DEBUG;
    };

} // namespace gir