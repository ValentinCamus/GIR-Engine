#include "TextureLoader.hpp"

#include <stb_image.h>

namespace gir
{
    Texture2D* TextureLoader::Load(const std::string &filename, bool flipYAxis)
    {
        Logger::Info("Loading image \"{0}\"...", filename);

        stbi_set_flip_vertically_on_load(flipYAxis);

        int width = 0;
        int height = 0;
        int nChannels = 0;
        const char * cPath = filename.c_str();

        const unsigned char* pixels = stbi_load(cPath, &width, &height, &nChannels, 0);
        GIR_ASSERT(pixels, "TextureLoader::Load: Image not found");

        auto* texture = new Texture2D(filename, GetFormat(nChannels), GL_UNSIGNED_BYTE);
        texture->Bind(0);
        texture->Allocate(width, height, pixels);
        texture->Unbind();

        Logger::Info("Image \"{0}\" was correctly loaded", filename);

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