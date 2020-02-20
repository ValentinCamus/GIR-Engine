#include "Texture.hpp"

namespace gir
{
    Texture::Texture(const std::string& name,
                     int internalFormat,
                     int format,
                     int dataType,
                     int textureType,
                     bool generateMipmap) :
        OpenGLComponent(name),
        m_internalFormat(internalFormat),
        m_format(format),
        m_dataType(dataType),
        m_textureType(textureType),
        m_generateMipmap(generateMipmap)
    {
        glGenTextures(1, &m_id);

        Bind();

        // Default parameters:
        if (m_generateMipmap) SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        else SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (m_textureType == GL_TEXTURE_2D)
        {
            SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
            SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else if (m_textureType == GL_TEXTURE_CUBE_MAP) // Only used for shadow maps as of today
        {
            SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            SetParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }
        else
        {
            Logger::Error("Invalid texture type");
        }

        Unbind();
    }

    Texture::~Texture() { glDeleteTextures(1, &m_id); }

    void Texture::Allocate(unsigned width, unsigned height, const unsigned char* pixels)
    {
        GIR_ASSERT(IsBound(), "Texture::Resize: The texture needs to be bound to be resized");
        m_width  = width;
        m_height = height;

        if (m_textureType == GL_TEXTURE_2D)
        {
            glTexImage2D(m_textureType, 0, m_internalFormat, m_width, m_height, 0, m_format, m_dataType, pixels);
        }
        else
        {
            for (int i = 0; i < 6; ++i)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0,
                             m_internalFormat,
                             m_width,
                             m_height,
                             0,
                             m_format,
                             m_dataType,
                             nullptr);
        }

        if (m_generateMipmap) glGenerateMipmap(m_textureType);
    }

    void Texture::Bind()
    {
        OpenGLComponent::Bind();
        glBindTexture(m_textureType, m_id);
    }

    void Texture::Unbind()
    {
        OpenGLComponent::Unbind();
        glBindTexture(m_textureType, 0);
    }

    void Texture::Bind(int slot)
    {
        m_slot = slot;
        glActiveTexture(GL_TEXTURE0 + (GLenum)m_slot);
        Bind();
    }

    void Texture::SetParameter(int name, int value)
    {
        GIR_ASSERT(IsBound(), "Texture::SetParameter (int): To set a parameter, the texture needs to be bound");
        glTexParameteri(m_textureType, name, value);
    }

    void Texture::SetParameter(int name, float value)
    {
        GIR_ASSERT(IsBound(), "Texture::SetParameter (float): To set a parameter, the texture needs to be bound");
        glTexParameterf(m_textureType, name, value);
    }
} // namespace gir