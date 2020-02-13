#pragma once

#include <imgui.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

namespace gir
{
    class ViewportWidget : public ImGuiWidget
    {
    public:
        /// Initialize the widget.
        /// @warning: needs to be initialized after the renderer initialization (e.g glad).
        ViewportWidget(const char* name, unsigned width, unsigned height, bool isVisible = true);

        /// Destructor.
        ~ViewportWidget() override;

        void Draw() override;

        /// @return: The viewport's framebuffer.
        inline Framebuffer* GetFramebuffer() { return m_framebuffer; }

        /// @return: The viewport's width.
        /// @note: The viewport's dimension is different from the application's window dimension.
        inline unsigned GetWidth() const { return m_framebuffer->GetTexture(0)->GetWidth(); }

        /// @return: The viewport's height.
        /// @note: The viewport's dimension is different from the application's window dimension.
        inline unsigned GetHeight() const { return m_framebuffer->GetTexture(0)->GetHeight(); }

    private:
        /// @return: The framebuffer dimension.
        ImVec2 GetFramebufferSize() const;

        /// @return: true if the size of the window and the framebuffer doesn't match.
        bool ShouldResizeFramebuffer() const;

        /// Resize the framebuffer with the current window size.
        void ResizeFramebuffer();

        /// Draw the framebuffer's texture at the attachment: GL_COLOR_ATTACHMENT0.
        void DrawFramebuffer();

    private:
        /// Where the framebuffer will draw the scene.
        Texture2D* m_texture = nullptr;

        Framebuffer* m_framebuffer = nullptr;
    };
} // namespace gir
