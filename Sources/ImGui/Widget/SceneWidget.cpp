#include "SceneWidget.hpp"

namespace gir
{
    void SceneWidget::Draw()
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

        if (m_scene)
        {
            m_components.clear();

            std::vector<const char*> sceneItems = {"<No Selection>"};

            for (const std::unique_ptr<Light>& light : m_scene->GetLights())
            {
                sceneItems.emplace_back(light->GetName().c_str());
                m_components.push_back(light.get());
            }

            for (const std::unique_ptr<Entity>& entity : m_scene->GetEntities())
            {
                sceneItems.emplace_back(entity->GetName().c_str());
                m_components.push_back(entity.get());
            }

            ImGui::Text("Scene hierarchy:");
            ImGui::ListBox("##hierarchy", &m_selectedIndex, sceneItems.data(), sceneItems.size(), 8);
        }

        ImGui::End();
    }

    SceneComponent* SceneWidget::GetSelectedComponent() const
    {
        return IsSelectionValid() ? m_components.at(m_selectedIndex - 1) : nullptr;
    }

} // namespace gir