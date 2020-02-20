#pragma once

#include <Core/Core.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

namespace gir
{
    class ImageWriter
    {
    public:
        static void Save(Framebuffer* framebuffer, bool applyGammaCorrection = true);

    private:
        static std::string GenerateFileName();
    };
}


