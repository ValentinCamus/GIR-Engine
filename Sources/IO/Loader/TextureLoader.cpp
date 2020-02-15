#include "TextureLoader.hpp"
#include <Engine/Manager/Manager.hpp>

#include <stb_image.h>

namespace gir
{
    Texture2D* TextureLoader::Load(const std::string &filename, bool flipYAxis)
    {
        int width = 0;
        int height = 0;
        int nChannels = 0;
        const char * cPath = filename.c_str();

        const unsigned char* pixels = stbi_load(cPath, &width, &height, &nChannels, 0);
        if (!pixels)
        {
            Logger::Warn("TextureLoader::Load: Image not found " + filename);
            return nullptr;
        }

        auto* texture = Manager<Texture2D>::Add(filename, GetFormat(nChannels), GL_UNSIGNED_BYTE, true);
        texture->Bind(0);
        texture->Allocate(width, height, pixels);
        texture->Unbind();

        Logger::Info("Texture \"{0}\": Loaded", filename);

        return texture;
    }

    int TextureLoader::GetFormat(unsigned nChannels)
    {
        GIR_ASSERT(nChannels <= 4, "TextureLoader: More than 4 channels is not supported");

        switch (nChannels)
        {
            case 1: return GL_RED;
            case 2: return GL_RG;
            case 3: return GL_RGB;
            default: return GL_RGBA;
        }
    }
}