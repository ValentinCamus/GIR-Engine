#include "TransformEditorWidget.hpp"

namespace gir
{
    ImGuizmo::MODE TransformEditorWidget::currentGizmoMode = ImGuizmo::LOCAL;

    ImGuizmo::OPERATION TransformEditorWidget::currentGizmoOperation = ImGuizmo::TRANSLATE;

    void TransformEditorWidget::Draw()
    {
        ImGuizmo::BeginFrame();

        ImGui::SetWindowPos(ImVec2(64, 64), ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize(ImVec2(512, 512), ImGuiCond_FirstUseEver);

        if (!ImGui::Begin(GetName(), &m_isVisible))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        if (m_component)
        {
            Mat4f model = m_component->GetTransform();
            float* imGuizmoModel = glm::value_ptr(model);

            if (ImGui::RadioButton("Translate", currentGizmoOperation == ImGuizmo::TRANSLATE))
            {
                currentGizmoOperation = ImGuizmo::TRANSLATE;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("Rotate", currentGizmoOperation == ImGuizmo::ROTATE))
            {
                currentGizmoOperation = ImGuizmo::ROTATE;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("Scale", currentGizmoOperation == ImGuizmo::SCALE))
            {
                currentGizmoOperation = ImGuizmo::SCALE;
            }

            float matrixTranslation[3], matrixRotation[3], matrixScale[3];
            ImGuizmo::DecomposeMatrixToComponents(imGuizmoModel, matrixTranslation, matrixRotation, matrixScale);
            ImGui::InputFloat3("Tr", matrixTranslation, 3);
            ImGui::InputFloat3("Rt", matrixRotation, 3);
            ImGui::InputFloat3("Sc", matrixScale, 3);
            ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, imGuizmoModel);

            if (currentGizmoOperation != ImGuizmo::SCALE)
            {
                if (ImGui::RadioButton("Local", currentGizmoMode == ImGuizmo::LOCAL))
                {
                    currentGizmoMode = ImGuizmo::LOCAL;
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("World", currentGizmoMode == ImGuizmo::WORLD))
                {
                    currentGizmoMode = ImGuizmo::WORLD;
                }
            }

            // Update the component model matrix
            m_component->SetTransform(glm::make_mat4(imGuizmoModel));
        }

        ImGui::End();
    }
}