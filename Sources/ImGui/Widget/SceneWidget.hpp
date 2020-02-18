#pragma once

#include <imgui.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>

#include <Engine/Scene/Scene.hpp>

namespace gir
{
    class SceneWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        void Draw() override;

        SceneComponent* GetSelectedComponent() const;

        inline bool IsSelectionValid() const { return m_selectedIndex > 0; }

        inline void SetScene(const Scene* scene) { m_scene = scene; }

    private:
        const Scene* m_scene = nullptr;

        std::vector<SceneComponent*> m_components;

        int m_selectedIndex = 0;
    };
} // namespace gir
