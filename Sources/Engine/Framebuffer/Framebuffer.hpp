#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/OpenGLComponent.hpp>
#include <Engine/Texture/Texture2D.hpp>

namespace gir
{
    class Framebuffer : public OpenGLComponent
    {
    public:
        /// Constructor.
        explicit Framebuffer(const std::string& name);

        /// Destructor.
        ~Framebuffer() override;

        /// Resize the framebuffer with the given dimension.
        void Resize(unsigned width, unsigned height);

        /// Attach a render buffer to the framebuffer.
        /// @format: specifies the internal format to use for the renderbuffer object's image.
        /// @attachment: specifies the attachment point to which renderbuffer should be attached.
        void AttachRenderbuffer(int format, int attachment);

        /// Attach a texture to the framebuffer.
        /// @texture: the texture to attach.
        /// @attachment: specifies the attachment point to which an image from texture should be attached.
        void AttachTexture(Texture2D* texture, int attachment);

        void Bind() override;

        void Unbind() override;

        /// @return: true if the framebuffer is complete.
        bool IsComplete() const;

        inline bool IsRenderbufferAttached() const { return m_rbo > 0; }

        inline bool HasTexturesAttached() const { return !m_textures.empty(); }

        inline Texture2D* GetTexture(unsigned i) { return m_textures[i]; }

        inline unsigned TextureCount() const { return static_cast<unsigned>(m_textures.size()); }

        float GetAspectRatio() const;

    private:
        /// Renderbuffer's id.
        unsigned m_rbo = 0;

        unsigned m_width  = 0;
        unsigned m_height = 0;

        std::vector<Texture2D*> m_textures {};
    };
} // namespace gir