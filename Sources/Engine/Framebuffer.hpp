#pragma once

#include <Core/Core.hpp>
#include <Engine/Bindable.hpp>
#include <Engine/Texture2D.hpp>

namespace gir
{
    class Framebuffer : public Bindable
    {
    public:
        /// Constructor.
        /// @name: the framebuffer's name.
        explicit Framebuffer(const char* name);

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

        inline bool IsBound() const override { return m_isBound; }

        inline unsigned GetId() const override { return m_fbo; }

        inline const char* GetName() const override { return m_name; }

        /// @return: true if the framebuffer is complete.
        bool IsComplete() const;

        inline bool IsRenderbufferAttached() const { return m_rbo > 0; }

        inline bool IsTextureAttached() const { return m_texture != nullptr; }

        inline const Texture2D* GetTexture() const { return m_texture; }

        float GetAspectRatio() const;

    private:
        const char* m_name;

        /// Framebuffer's id.
        unsigned m_fbo = 0;

        /// Renderbuffer's id.
        unsigned m_rbo = 0;

        unsigned m_width = 0;
        unsigned m_height = 0;

        bool m_isBound = false;

        Texture2D* m_texture = nullptr;
    };
}