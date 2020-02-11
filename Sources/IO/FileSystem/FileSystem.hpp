#pragma once

#include <Core/Core.hpp>

namespace gir
    {
    class FileSystem
    {
    public:
        static std::string GetProjectDir() { return PROJECT_SOURCE_DIR; }

        static std::string GetAssetsDir() { return PROJECT_SOURCE_DIR"/Assets/"; }

        static std::string GetShadersDir() { return PROJECT_SOURCE_DIR"/Shaders/"; }
    };
}



