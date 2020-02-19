#pragma once

#include <future>

#include <Core/Core.hpp>

#include <Engine/Texture/Texture.hpp>

namespace gir
{
    class TextureLoader
    {
    public:
        static Texture* Load(const std::string& filename);

    private:
        static int GetFormat(unsigned nChannels);
    };
}



