#pragma once

#include <Core/Core.hpp>

#include <Engine/Texture/Texture2D.hpp>

namespace gir
{
    class TextureLoader
    {
    public:
        static Texture2D* Load(const std::string& filename, bool flipYAxis = true);

        template<typename Callback>
        static void AsyncLoad(const std::string& filename, Callback callback);

        static void Wait();
    };
}



