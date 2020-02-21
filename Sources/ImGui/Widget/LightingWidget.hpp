#pragma once

#include <imgui.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>

#include <Engine/Light/DirectionalLight.hpp>
#include <Engine/Light/SpotLight.hpp>
#include <Engine/Light/PointLight.hpp>

namespace gir
{
    enum class ELightingMode
    {
        UNLIT  = 0,
        DIRECT = 1,
        RSM    = 2,
        RSMGS  = 3
    };
    constexpr const char* LIGHTING_MODES[] = {"Unlit", "Direct", "RSM", "RSM + GS"};

    class LightingWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        void Draw() override;

        inline ELightingMode GetLightingMode() const { return static_cast<ELightingMode>(m_selectedLightingMode); }

        inline void SetLight(Light* light) { m_light = light; }

    private:
        Light* m_light = nullptr;

        int m_selectedLightingMode = 1;
    };
} // namespace gir
