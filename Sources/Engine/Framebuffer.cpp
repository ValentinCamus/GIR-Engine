#include "Framebuffer.hpp"

#include <glad/glad.h>

namespace gir
{
    Framebuffer::Framebuffer(const char* name)
        : m_name(name)
    {
        glGenFramebuffers(1, &m_fbo);
    }

    Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &m_fbo); }

    void Framebuffer::Resize(unsigned width, unsigned height)
    {
        m_width  = width;
        m_height = height;
        glViewport(0, 0, width, height);

        if (IsRenderbufferAttached())
        {
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        }

        if (m_texture)
        {
            m_texture->Bind();
            m_texture->Allocate(width, height);
        }
    }

    void Framebuffer::Bind()
    {
        GIR_ASSERT(m_fbo > 0, "Invalid framebuffer's ID");

        glViewport(0, 0, m_width, m_height);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    float Framebuffer::GetAspectRatio() const { return float(m_width) / float(m_height); }

    void Framebuffer::AttachRenderbuffer(int format, int attachment)
    {
        GIR_ASSERT(!IsRenderbufferAttached(), "Framebuffer::AttachRenderbuffer: A Renderbuffer is already attached");

        // Create a renderbuffer object for depth and stencil attachment
        glGenRenderbuffers(1, &m_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);

        // Use a single renderbuffer object for both a depth AND stencil buffer.
        glRenderbufferStorage(GL_RENDERBUFFER, format, m_width, m_height);

        // Attach the render buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, m_rbo);
    }

    void Framebuffer::AttachTexture(Texture2D* texture, int attachment)
    {
        GIR_ASSERT(m_texture == nullptr, "A texture is already attached");

        m_texture = texture;
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetId(), 0);
    }

    bool Framebuffer::IsComplete() const { return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE; }
} // namespace gir