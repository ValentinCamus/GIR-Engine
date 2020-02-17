#pragma once

#include <Core/Core.hpp>
#include <Engine/OpenGL/OpenGL.hpp>
#include <IO/Input/Input.hpp>
#include <Application/Window.hpp>
#include <ImGui/ImGuiController.hpp>
#include <ImGui/Widget/Widget.hpp>
#include <Application/WindowEventListener.hpp>
#include <Engine/Texture/Texture2D.hpp>
#include <Engine/Scene/Scene.hpp>
#include <Engine/Renderer/Renderer.hpp>
#include <Engine/Camera/CameraController.hpp>

#include <GLFW/glfw3.h>

#define DEFAULT_APP_NAME "Application"
#define DEFAULT_APP_WIDTH 800
#define DEFAULT_APP_HEIGHT 600

namespace gir
{
    class Application : public WindowEventListener
    {
    public:
        /// Default constructor.
        explicit Application(const char* name = DEFAULT_APP_NAME,
                             unsigned width   = DEFAULT_APP_WIDTH,
                             unsigned height  = DEFAULT_APP_HEIGHT);

        /// Default destructor.
        ~Application() override = default;

        /// Setup and start the draw loop.
        void Run();

        /// Stop the draw loop and close the application.
        void Stop();

        /// Define the base application setup.
        virtual void Setup();

        /// Called when the application is closing.
        virtual void Shutdown();

        /// Called just before the draw loop.
        virtual void Prepare(float deltaTime);

        /// Draw loop.
        virtual void Draw(float deltaTime);

        /// GUI draw loop.
        virtual void ImGuiDraw(float deltaTime);

        /// Check if the application is running.
        inline bool IsRunning() const { return m_isRunning; }

        /// Event called when the user attempts to close the window.
        void OnWindowClosed() override;

        /// Event called when the mouse position changed.
        void OnMouseMoved(double xPos, double yPos) override;

        /// Event called when a scrolling device is used.
        void OnMouseScrolled(double xOffset, double yOffset) override;

    private:
        bool m_isRunning = false;

        /// The timer measures time elapsed since the application was initialized.
        double m_time = 0.0f;

        Window m_window = Window();

        Input m_input = Input();

        CameraController m_cameraController = CameraController(nullptr);

        ImGuiController m_gui = ImGuiController();

        ViewportWidget m_viewport = ViewportWidget("Viewport");

        StatsWidget m_statsWidget = StatsWidget("Statistics");

        LightingWidget m_lightingWidget = LightingWidget("Lighting");

        std::unique_ptr<Scene> m_scene = nullptr;

        std::unique_ptr<Renderer> m_renderer = nullptr;
    };
} // namespace gir
