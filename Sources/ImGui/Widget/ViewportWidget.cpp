#include "ViewportWidget.hpp"

namespace gir
{
    void ViewportWidget::Init(unsigned width, unsigned height)
    {
        m_texture     = new Texture2D("Default texture", GL_RGB, GL_UNSIGNED_INT);
        m_framebuffer = new Framebuffer("Default framebuffer");

        m_framebuffer->Bind();
        m_framebuffer->AttachTexture(m_texture, GL_COLOR_ATTACHMENT0);
        m_framebuffer->AttachRenderbuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        m_framebuffer->Resize(width, height);
        m_framebuffer->Unbind();

        GIR_ASSERT(m_framebuffer->IsComplete(), "Framebuffer is not complete");
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

        if (ShouldResizeFramebuffer()) { ResizeFramebuffer(); }
        else
        {
            DrawFramebuffer();
        }

        ImGui::End();
    }

    ViewportWidget::~ViewportWidget()
    {
        delete m_framebuffer;
        delete m_texture;
    }

    ImVec2 ViewportWidget::GetFramebufferSize() const
    {
        auto fbWidth  = (float)m_framebuffer->GetTexture(0)->GetWidth();
        auto fbHeight = (float)m_framebuffer->GetTexture(0)->GetHeight();
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
} // namespace gir