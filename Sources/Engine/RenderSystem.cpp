#include "RenderSystem.hpp"

namespace gir
{
    RenderSystem::RenderSystem(const Scene& scene) : m_scene {scene}, m_shaderManager {{}}, m_GBuffer {}
    {
        // TODO: add textures to the framebuffer and fill the shader manager initializer
    }

    void RenderSystem::draw()
    {
        switch (m_renderMode)
        {
            case RenderMode::DEBUG:
                break;
            case RenderMode::RSM:
                break;
            default:
                Logger::Error("[ERROR]: Invalid render mode");
                break;
        }
    }

    void RenderSystem::ReloadShaders() { m_shaderManager = ShaderManager {{}}; }

    void RenderSystem::SetRenderMode(RenderMode mode) { m_renderMode = mode; }

} // namespace gir