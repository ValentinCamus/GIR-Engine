#include "Framebuffer.hpp"

#include <glad/glad.h>

namespace gir
{
    Framebuffer::Framebuffer(const std::string& name) : OpenGLComponent(name) { glGenFramebuffers(1, &m_id); }

    Framebuffer::~Framebuffer()
    {
        if (IsRenderbufferAttached()) glDeleteRenderbuffers(1, &m_rbo);

        glDeleteFramebuffers(1, &m_id);
    }

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

        for (auto &texture : m_textures)
        {
            texture->Bind();
            texture->Allocate(width, height);
            texture->Unbind();
        }
    }

    void Framebuffer::Bind()
    {
        GIR_ASSERT(GetId() > 0, "Invalid framebuffer's ID");

        OpenGLComponent::Bind();

        glViewport(0, 0, m_width, m_height);
        glBindFramebuffer(GL_FRAMEBUFFER, GetId());
    }

    void Framebuffer::Unbind()
    {
        OpenGLComponent::Unbind();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::BlitDepthBuffer(const Framebuffer* target) const
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target->m_id);
        glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }

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

    void Framebuffer::AttachTexture(std::unique_ptr<Texture2D>&& texture, int attachment)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetId(), 0);
        m_textures.emplace_back(std::move(texture));
    }

    bool Framebuffer::IsComplete() const { return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE; }
} // namespace gir