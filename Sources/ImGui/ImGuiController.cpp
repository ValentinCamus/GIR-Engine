#include "ImGuiController.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_gl3.h"

namespace gir
{
    void ImGuiController::Init(GLFWwindow* window)
    {
        GIR_ASSERT(window, "ImGuiController::Init: Invalid parameter");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        ImGui::GetStyle().WindowRounding = 0.0f;
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 1.0f;

        m_window = window;
        SetupPlatformBindings();

        ImGui::GetIO().IniFilename = PROJECT_SOURCE_DIR"/Data/ImGui.ini";

        Logger::Info("ImGui: Initialized");
    }

    void ImGuiController::Shutdown()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();

        Logger::Info("ImGui: Shutdown");
    }

    void ImGuiController::BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        UpdateDocker();
    }

    void ImGuiController::EndFrame()
    {
        UpdateDisplaySize();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }
    }

    void ImGuiController::SetupPlatformBindings()
    {
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiController::UpdateDocker()
    {
        static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dock-able into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
        windowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) windowFlags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become un-docked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dock space/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        static bool isOpen = true;
        ImGui::Begin("Docker", &isOpen, windowFlags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiID dockSpaceId = ImGui::GetID("Docker");
        ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), dockSpaceFlags);

        ImGui::End();
    }

    void ImGuiController::UpdateDisplaySize()
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        ImGui::GetIO().DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));
    }
}