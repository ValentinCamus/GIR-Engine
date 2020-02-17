#pragma once

#include <future>

#include <Core/Core.hpp>

#include <Engine/Texture/Texture2D.hpp>

namespace gir
{
    class TextureLoader
    {
    public:
        static Texture2D* Load(const std::string& filename);

    private:
        static int GetFormat(unsigned nChannels);
    };
}



