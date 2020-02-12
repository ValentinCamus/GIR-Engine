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

        inline Framebuffer* GetFramebuffer() { return m_framebuffer; }

    private:
        ImVec2 GetFramebufferSize() const;

        /// @return: true if the size of the window and the framebuffer doesn't match.
        bool ShouldResizeFramebuffer() const;

        /// Resize the framebuffer with the current window size.
        void ResizeFramebuffer();

        void DrawFramebuffer();

    private:
        /// Where the framebuffer will draw the scene.
        Texture2D* m_texture = nullptr;

        Framebuffer* m_framebuffer = nullptr;
    };
} // namespace gir
