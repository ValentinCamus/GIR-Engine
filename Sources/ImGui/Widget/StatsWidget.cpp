#include "StatsWidget.hpp"

#include <glad/glad.h>

namespace gir
{
    void StatsWidget::Draw()
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({300.0f, 300.0f}, ImGuiCond_FirstUseEver);

        if (!m_isVisible) return;

        // Main body of the Demo window starts here.
        if (!ImGui::Begin(GetName(), &m_isVisible))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        float fps                                     = ImGui::GetIO().Framerate;
        m_fpsHistory[(m_cursor++) % MAX_HISTORY_SIZE] = fps;

        ImGui::Text("Framerate: %f", fps);
        ImGui::PlotLines("##fps", m_fpsHistory.data(), m_fpsHistory.size());

        ImGui::NewLine();

        ImGui::Text("Renderer:");
        ImGui::Text("> %s", glGetString(GL_RENDERER));
        ImGui::Text("Vendor:");
        ImGui::Text("> %s", glGetString(GL_VENDOR));
        ImGui::Text("Version:");
        ImGui::Text("> %s", glGetString(GL_VERSION));

        ImGui::End();
    }
} // namespace gir