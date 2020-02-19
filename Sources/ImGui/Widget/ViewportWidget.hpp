#pragma once

#include <imgui.h>
#include <ImGuizmo.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

#include <Engine/Component/SceneComponent.hpp>

namespace gir
{
    class ViewportWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        /// Destructor.
        ~ViewportWidget() override = default;

        /// Initialize the widget.
        /// @warning: needs to be initialized after the renderer initialization (e.g glad).
        void Init(unsigned width, unsigned height);

        void Shutdown();

        void Draw() override;

        inline Framebuffer* GetFramebuffer() { return m_framebuffer; }

        void DrawGizmo(const Mat4f& projection, const Mat4f& view, SceneComponent* component);

    private:
        ImVec2 GetFramebufferSize() const;

        /// @return: true if the size of the window and the framebuffer doesn't match.
        bool ShouldResizeFramebuffer() const;

        /// Resize the framebuffer with the current window size.
        void ResizeFramebuffer();

        void DrawFramebuffer();

        void DrawGizmo();

    private:
        Framebuffer* m_framebuffer = nullptr;

        const float* m_view = nullptr;
        const float* m_projection = nullptr;

        SceneComponent* m_component = nullptr;
    };
} // namespace gir
