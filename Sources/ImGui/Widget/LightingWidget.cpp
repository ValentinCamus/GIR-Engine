#include "LightingWidget.hpp"

namespace gir
{
    void LightingWidget::Draw()
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({300.0f, 300.0f}, ImGuiCond_FirstUseEver);

        // Main body of the Demo window starts here.
        if (!ImGui::Begin(GetName(), &m_isVisible))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        std::vector<const char*> lights = {"<No Selection>"};
        // TODO: Retrieve the array of Lights* from the scene and append each light's name to to @lights.
        ImGui::ListBox("Lights", &m_selectedIndex, lights.data(), lights.size(), 8);

        ImGui::Combo("Mode", &m_selectedLightingMode, LIGHTING_MODES, IM_ARRAYSIZE(LIGHTING_MODES));

        ImGui::End();
    }
}