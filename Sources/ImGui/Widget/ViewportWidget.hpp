#pragma once

#include <imgui.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>
#include <Engine/Framebuffer.hpp>

namespace gir
{
    class ViewportWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        /// Destructor.
        ~ViewportWidget() override;

        /// Initialize the widget.
        /// @warning: needs to be initialized after the renderer initialization (e.g glad).
        void Init(unsigned width, unsigned height);

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
