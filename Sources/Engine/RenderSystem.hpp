#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "Scene.hpp"
#include "Framebuffer.hpp"


namespace gir {

// TODO: do
class RenderSystem {
public:
    RenderSystem(Scene &scene);
    
private:
    Framebuffer m_GBuffer;
};

} // namespace gir

#endif