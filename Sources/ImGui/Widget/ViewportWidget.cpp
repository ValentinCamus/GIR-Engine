#include "ViewportWidget.hpp"

#include <ImGui/Widget/TransformEditorWidget.hpp>

namespace gir
{
    void ViewportWidget::Init(unsigned width, unsigned height)
    {
        m_framebuffer = new Framebuffer("Default framebuffer");

        m_framebuffer->Bind();
        m_framebuffer->AttachTexture(std::make_unique<Texture>("Default texture", GL_RGBA32F, GL_RGBA, GL_FLOAT), GL_COLOR_ATTACHMENT0);
        m_framebuffer->AttachRenderbuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        m_framebuffer->Resize(width, height);
        m_framebuffer->Unbind();

        GIR_ASSERT(m_framebuffer->IsComplete(), "Framebuffer is not complete");
    }

    void ViewportWidget::Shutdown()
    {
        delete m_framebuffer;
    }

    void ViewportWidget::Draw()
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(GetFramebufferSize(), ImGuiCond_FirstUseEver);

        if (!m_isVisible) return;

        // Main body of the Demo window starts here.
        if (!ImGui::Begin(GetName(), &m_isVisible))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        if (ShouldResizeFramebuffer())
        {
            ResizeFramebuffer();
        }
        else
        {
            DrawFramebuffer();
        }

        if (m_projection && m_view && m_component)
        {
            DrawGizmo();
        }

        ImGui::End();
    }

    ImVec2 ViewportWidget::GetFramebufferSize() const
    {
        auto fbWidth  = (float) m_framebuffer->GetTexture(0)->GetWidth();
        auto fbHeight = (float) m_framebuffer->GetTexture(0)->GetHeight();
        return {fbWidth, fbHeight};
    }

    bool ViewportWidget::ShouldResizeFramebuffer() const
    {
        ImVec2 winSize = ImGui::GetWindowSize();
        ImVec2 fbSize  = GetFramebufferSize();
        return winSize.x != fbSize.x || winSize.y != fbSize.y;
    }

    void ViewportWidget::ResizeFramebuffer()
    {
        ImVec2 winSize = ImGui::GetWindowSize();
        auto width     = (unsigned)winSize.x;
        auto height    = (unsigned)winSize.y;

        m_framebuffer->Bind();
        m_framebuffer->Resize(width, height);
        m_framebuffer->Unbind();
    }

    void ViewportWidget::DrawFramebuffer()
    {
        ImVec2 winSize = ImGui::GetWindowSize();
        m_framebuffer->Bind();
        void* id = (void*)(uintptr_t)m_framebuffer->GetTexture(0)->GetId();
        ImGui::Image(id, winSize, ImVec2(0, 1), ImVec2(1, 0));
        m_framebuffer->Unbind();
    }

    void ViewportWidget::DrawGizmo()
    {
        Mat4f model = m_component->GetTransform();
        float* imGuizmoModel = glm::value_ptr(model);

        ImVec2 winPos = ImGui::GetWindowPos();
        ImVec2 winSize = ImGui::GetWindowSize();

        ImGuizmo::MODE mode = TransformEditorWidget::currentGizmoMode;
        ImGuizmo::OPERATION operation = TransformEditorWidget::currentGizmoOperation;

        ImGuizmo::SetRect(winPos.x, winPos.y, winSize.x, winSize.y);
        ImGuizmo::SetDrawlist();
        ImGuizmo::Manipulate(m_view, m_projection, operation, mode, imGuizmoModel);

        // Update the component model matrix
        m_component->SetTransform(glm::make_mat4(imGuizmoModel));
    }

    void ViewportWidget::DrawGizmo(const Mat4f &projection, const Mat4f &view, SceneComponent *component)
    {
        m_component = component;

        m_view = glm::value_ptr(view);
        m_projection = glm::value_ptr(projection);
    }

} // namespace gir