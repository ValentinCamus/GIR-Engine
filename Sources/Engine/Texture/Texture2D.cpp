#include "Texture2D.hpp"

namespace gir
{
    Texture2D::Texture2D(const std::string& name, int format, int type) :
        OpenGLComponent {name},
        m_format(format),
        m_internalFormat(format),
        m_type(type)
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

    Texture2D::Texture2D(const std::string& name, int format, int internalFormat, int type) :
            OpenGLComponent {name},
            m_format(format),
            m_internalFormat(internalFormat),
            m_type(type)
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

    Texture2D::~Texture2D() { glDeleteTextures(1, &m_id); }

    void Texture2D::Allocate(unsigned width, unsigned height, const unsigned char* pixels)
    {
        GIR_ASSERT(IsBound(), "Texture2D::Resize: The texture needs to be bound to be resized");
        m_width  = width;
        m_height = height;
        glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, m_internalFormat, m_type, pixels);
    }

    void Texture2D::Bind()
    {
        OpenGLComponent::Bind();
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture2D::Unbind()
    {
        OpenGLComponent::Unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::Bind(int slot)
    {
        m_slot = slot;
        glActiveTexture(GL_TEXTURE0 + (GLenum)slot);
        Bind();
    }

    void Texture2D::SetParameter(int name, int value)
    {
        GIR_ASSERT(IsBound(), "Texture2D::SetParameter (int): To set a parameter, the texture needs to be bound");
        glTexParameteri(GL_TEXTURE_2D, name, value);
    }

    void Texture2D::SetParameter(int name, float value)
    {
        GIR_ASSERT(IsBound(), "Texture2D::SetParameter (float): To set a parameter, the texture needs to be bound");
        glTexParameterf(GL_TEXTURE_2D, name, value);
    }
} // namespace gir