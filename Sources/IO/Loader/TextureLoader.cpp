#include "TextureLoader.hpp"
#include <Engine/Manager/Manager.hpp>

#include <stb_image.h>

namespace gir
{
    Texture* TextureLoader::Load(const std::string& filename)
    {
        int width         = 0;
        int height        = 0;
        int nChannels     = 0;
        const char* cPath = filename.c_str();

        const unsigned char* pixels = stbi_load(cPath, &width, &height, &nChannels, 0);
        if (!pixels)
        {
            Logger::Warn("TextureLoader::Load: Image not found " + filename);
            return nullptr;
        }
        auto format   = GetFormat(nChannels);
        auto* texture = Manager<Texture>::Add(filename, format, format, GL_UNSIGNED_BYTE, GL_TEXTURE_2D, true);
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
            case 1:
                return GL_RED;
            case 2:
                return GL_RG;
            case 3:
                return GL_RGB;
            default:
                return GL_RGBA;
        }
    }
    
    // TODO: Watch out for normal maps
    int TextureLoader::GetInternalFormat(unsigned nChannels)
    {
        GIR_ASSERT(nChannels <= 4, "TextureLoader: More than 4 channels is not supported");

        switch (nChannels)
        {
            case 1:
                return GL_RED;
            case 2:
                return GL_RG;
            case 3:
                return GL_SRGB;
            default:
                return GL_SRGB_ALPHA;
        }
    }
} // namespace gir