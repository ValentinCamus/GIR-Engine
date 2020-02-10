#include "Renderer.hpp"

namespace gir
{
    Renderer::Renderer(const Scene& scene)
        : m_scene {scene}
        , m_shaderManager {{}}
        , m_gBuffer {"GBuffer"}
    {
        // TODO: add textures to the framebuffer and fill the shader manager initializer
    }

    void Renderer::Draw()
    {
        switch (m_renderMode)
        {
            case RenderMode::DEBUG:
                break;
            case RenderMode::RSM:
                break;
            default:
                Logger::Error("Invalid render mode");
                break;
        }
    }

    void Renderer::ReloadShaders() { m_shaderManager = ShaderManager {{}}; }

    void Renderer::SetRenderMode(RenderMode mode) { m_renderMode = mode; }

} // namespace gir