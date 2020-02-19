#include "LightingWidget.hpp"

namespace gir
{
    void LightingWidget::Draw()
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

        ImGui::Text("Lighting mode:");
        ImGui::ListBox("##modes", &m_selectedLightingMode, LIGHTING_MODES, IM_ARRAYSIZE(LIGHTING_MODES), 4);

        ImGui::End();
    }
} // namespace gir