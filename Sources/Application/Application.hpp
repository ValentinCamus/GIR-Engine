#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Core.hpp>
#include <IO/Input/Input.hpp>
#include <Application/Window.hpp>
#include <ImGui/ImGuiController.hpp>
#include <ImGui/Widget/Widget.hpp>
#include <Application/WindowEventListener.hpp>
#include <Engine/Texture/Texture2D.hpp>
#include <Engine/Scene/Scene.hpp>
#include <Engine/Renderer/Renderer.hpp>

#include <Engine/Camera/CameraController.hpp>

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
        ~Application() override;

        /// Setup and start the draw loop.
        void Run();

        /// Stop the draw loop and close the application.
        void Stop();

        /// Define the base application setup.
        virtual void Setup();

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

        float m_time = 0.0f;

        Input m_input;

        CameraController m_cameraController;

        Window* m_window = nullptr;

        ImGuiController* m_gui = nullptr;

        ViewportWidget* m_viewport = nullptr;

        StatsWidget* m_statsWidget = nullptr;

        LightingWidget* m_lightingWidget = nullptr;

        std::unique_ptr<Scene> m_scene = nullptr;

        std::unique_ptr<Renderer> m_renderer = nullptr;
    };
} // namespace gir
