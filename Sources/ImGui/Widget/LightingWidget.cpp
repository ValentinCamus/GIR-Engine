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

        if (m_light)
        {
            ImGui::NewLine();
            ImGui::Text("\"%s\" editor:", m_light->GetName().c_str());

            Vec3f color = m_light->GetColor();
            ImGui::InputFloat3("Color", glm::value_ptr(color), 3);
            m_light->SetColor(color);

            auto* spotLight = dynamic_cast<SpotLight*>(m_light);
            if (spotLight)
            {
                float innerAngle = spotLight->GetInnerAngle() * RAD2DEG;
                float outerAngle = spotLight->GetOuterAngle() * RAD2DEG;

                ImGui::InputFloat("Inner angle", &innerAngle, 1);
                ImGui::InputFloat("Outer angle", &outerAngle, 1);

                spotLight->SetInnerAngle(innerAngle * DEG2RAD);
                spotLight->SetOuterAngle(outerAngle * DEG2RAD);
            }
        }


        ImGui::End();
    }
} // namespace gir