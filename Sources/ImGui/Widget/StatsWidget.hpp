#pragma once

#include <imgui.h>

#include <Core/Core.hpp>
#include <ImGui/Widget/ImGuiWidget.hpp>

namespace gir
{
    constexpr unsigned FPS_LIMIT        = 512;
    constexpr unsigned MAX_HISTORY_SIZE = 512;

    class StatsWidget : public ImGuiWidget
    {
    public:
        /// Constructor.
        using ImGuiWidget::ImGuiWidget;

        void Draw() override;

    private:
        unsigned m_maxFPS = FPS_LIMIT;

        unsigned m_cursor = 0;

        std::array<float, MAX_HISTORY_SIZE> m_fpsHistory;
    };
} // namespace gir
