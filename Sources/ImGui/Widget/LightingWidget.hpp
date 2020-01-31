#pragma once

#include <imgui.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>

namespace gir
{
    enum class ELightingMode
    {
        Unlit = 0,
        Direct = 1,
        Global = 2
    };
    constexpr const char* LIGHTING_MODES[] = {"Unlit", "Direct", "Global"};

    class LightingWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        void Draw() override;

        inline int GetSelectedIndex() const { return m_selectedIndex - 1; }

        inline bool IsSelectedIndexValid() const { return m_selectedIndex > 0; }

        inline ELightingMode GetLightingMode() const { return static_cast<ELightingMode>(m_selectedLightingMode); }

    private:
        int m_selectedIndex = 0;

        int m_selectedLightingMode = 1;
    };
}


