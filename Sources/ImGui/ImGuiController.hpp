#pragma once

#include <imgui.h>
#include <imgui_impl_gl3.h>
#include <imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

#include <Core/Core.hpp>

namespace gir
{
    class ImGuiController
    {
    public:
        /// Initialize the controller.
        void Init(GLFWwindow* window);

        /// Terminate the current controller session.
        void Shutdown();

        /// Prepare the GUI renderer.
        void BeginFrame();

        /// End the GUI rendering.
        void EndFrame();

    private:
        void SetupPlatformBindings();

        /// Update the docking system.
        void UpdateDocker();

        /// Update ImGui display size.
        void UpdateDisplaySize();

    private:
        GLFWwindow* m_window = nullptr;
    };
} // namespace gir
