#include "Texture.hpp"

namespace gir
{
    Texture::Texture(const std::string& name, int internalFormat, int format, int type, bool generateMipmap) :
        OpenGLComponent(name),
        m_internalFormat(internalFormat),
        m_format(format),
        m_type(type),
        m_generateMipmap(generateMipmap)
    {
        glGenTextures(1, &m_id);

        Bind();

        // Default parameters:
        SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
        SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

        Unbind();
    }

    Texture::Texture(const std::string& name, int format, int type, bool generateMipmap) :
        OpenGLComponent {name},
        m_internalFormat(format),
        m_format(format),
        m_type(type),
        m_generateMipmap(generateMipmap)
    {
        glGenTextures(1, &m_id);

        Bind();

        // Default parameters:
        if (m_generateMipmap)
            SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        else
            SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
        SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

        Unbind();
    }

    Texture::~Texture() { glDeleteTextures(1, &m_id); }

    void Texture::Allocate(unsigned width, unsigned height, const unsigned char* pixels)
    {
        GIR_ASSERT(IsBound(), "Texture::Resize: The texture needs to be bound to be resized");
        m_width  = width;
        m_height = height;

        glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_format, m_type, pixels);

        if (m_generateMipmap) glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture::Bind()
    {
        OpenGLComponent::Bind();
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::Unbind()
    {
        OpenGLComponent::Unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Bind(int slot)
    {
        m_slot = slot;
        glActiveTexture(GL_TEXTURE0 + (GLenum)slot);
        Bind();
    }

    void Texture::SetParameter(int name, int value)
    {
        GIR_ASSERT(IsBound(), "Texture::SetParameter (int): To set a parameter, the texture needs to be bound");
        glTexParameteri(GL_TEXTURE_2D, name, value);
    }

    void Texture::SetParameter(int name, float value)
    {
        GIR_ASSERT(IsBound(), "Texture::SetParameter (float): To set a parameter, the texture needs to be bound");
        glTexParameterf(GL_TEXTURE_2D, name, value);
    }
} // namespace gir