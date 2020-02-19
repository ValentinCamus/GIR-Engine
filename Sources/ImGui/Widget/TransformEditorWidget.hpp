#pragma once

#include <imgui.h>
#include <ImGuizmo.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>

#include <Engine/Camera/Camera.hpp>
#include <Engine/Component/SceneComponent.hpp>

namespace gir
{
    class TransformEditorWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        /// Destructor.
        ~TransformEditorWidget() override = default;

        void Draw() override;

        inline SceneComponent* GetSceneComponent() { return m_component; }

        inline void SetSceneComponent(SceneComponent* component) { m_component = component; }

        static ImGuizmo::MODE currentGizmoMode;

        static ImGuizmo::OPERATION currentGizmoOperation;

    private:
        SceneComponent* m_component = nullptr;
    };
} // namespace gir
