#include "TextureLoader.hpp"

#include <stb_image.h>

namespace gir
{
    Texture2D *TextureLoader::Load(const std::string &filename, bool flipYAxis)
    {
        stbi_set_flip_vertically_on_load(flipYAxis);

        int width = 0, height = 0, channels = 0;
        const char * cPath = filename.c_str();

        Logger::Info("Loading image \"{0}\"...", filename);

        const unsigned char* pixels = stbi_load(cPath, &width, &height, &channels, 0);
        GIR_ASSERT(pixels, "TextureLoader::Load: Image not found");

        int format;
        switch (channels)
        {
            case 1:
                format = GL_RED;
                break;
            case 2:
                format = GL_RG;
                break;
            case 3:
                format = GL_RGB;
                break;
            default:
                format = GL_RGBA;
                break;
        }

        auto* texture = new Texture2D(filename, format, GL_UNSIGNED_BYTE);
        texture->Bind(0);
        texture->Allocate(width, height, pixels);
        texture->Unbind();

        Logger::Info("Image \"{0}\" was correctly loaded", filename);

        return texture;
    }

    template<typename Callback>
    void TextureLoader::AsyncLoad(const std::string &filename, Callback callback)
    {

    }

    void TextureLoader::Wait()
    {

    }
}