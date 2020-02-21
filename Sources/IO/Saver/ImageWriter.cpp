#include "ImageWriter.hpp"

#include <Engine/OpenGL/OpenGL.hpp>
#include <IO/FileSystem/FileSystem.hpp>

#include <stb_image_write.h>

namespace gir
{
    void ImageWriter::Save(Framebuffer* framebuffer, bool applyGammaCorrection)
    {
        std::string name = GenerateFileName();
        Logger::Info("Saving framebuffer \"{}\" as png image: GIR-Engine/Images/{}.png", framebuffer->GetName(), name);

        Texture* texture = framebuffer->GetTexture(0);
        unsigned width = texture->GetWidth();
        unsigned height = texture->GetHeight();

        glReadBuffer(GL_COLOR_ATTACHMENT0);
        auto* pixels = new float[width * height * 4];
        glReadPixels(0, 0, width, height, texture->GetFormat(), texture->GetDataType(), pixels);

        auto* rgbaPixels = new unsigned char[width * height * 4];
        for (unsigned i = 0; i < width * height * 4; i += 4)
        {
            float r = applyGammaCorrection ? std::pow(pixels[i + 0], 1.0f / 2.2f) : pixels[i + 0];
            float g = applyGammaCorrection ? std::pow(pixels[i + 1], 1.0f / 2.2f) : pixels[i + 1];
            float b = applyGammaCorrection ? std::pow(pixels[i + 2], 1.0f / 2.2f) : pixels[i + 2];

            rgbaPixels[i + 0] = r * 255;
            rgbaPixels[i + 1] = g * 255;
            rgbaPixels[i + 2] = b * 255;
            rgbaPixels[i + 3] = 255;
        }

        std::string filepath = FileSystem::GetProjectDir() + "/Images/" + name + ".png";

        stbi_flip_vertically_on_write(true);
        stbi_write_png(filepath.c_str(), (int) width, (int) height, 4, rgbaPixels, 4 * (int) width);
    }

    std::string ImageWriter::GenerateFileName()
    {
        time_t currentTime;
        time (&currentTime);
        auto* localTime = std::localtime(&currentTime);

        int year   = localTime->tm_year + 1900;
        int month  = localTime->tm_mon + 1;
        int day    = localTime->tm_mday;
        int hour   = localTime->tm_hour;
        int min    = localTime->tm_min;
        int sec    = localTime->tm_sec;

        std::stringstream ss;
        ss << year << "-" << month << "-" << day << "_" << hour << "." << min << "." << sec;

        return ss.str();
    }
}