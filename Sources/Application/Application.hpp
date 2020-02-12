#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Core.hpp>
#include <Application/Window.hpp>
#include <ImGui/ImGuiController.hpp>
#include <ImGui/Widget/Widget.hpp>
#include <Application/WindowEventListener.hpp>
#include <Engine/Texture/Texture2D.hpp>
#include <Engine/Scene/Scene.hpp>
#include <Engine/Renderer/Renderer.hpp>

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
        // TODO: add time step
        virtual void Setup();

        /// Called just before the draw loop.
        // TODO: add time step
        virtual void Prepare();

        /// Draw loop.
        // TODO: add time step
        virtual void Draw();

        /// GUI draw loop.
        // TODO: add time step
        virtual void ImGuiDraw();

        /// Check if the application is running.
        inline bool IsRunning() const { return m_isRunning; }

        /// Event called when the user attempts to close the window.
        void OnWindowClosed() override;

        /// Event called when the size of the window has changed.
        void OnWindowResize(int, int) override;

        /// Event called when a key is pressed.
        void OnKeyPressed(int keyCode) override;

        /// Event called when a key is released.
        void OnKeyReleased(int keyCode) override;

        /// Event called when a mouse button is pressed.
        void OnMousePressed(int button) override;

        /// Event called when a mouse button is released.
        void OnMouseReleased(int button) override;

        /// Event called when the mouse position changed.
        void OnMouseMoved(double xPos, double yPos) override;

        /// Event called when a scrolling device is used.
        void OnMouseScrolled(double xOffset, double yOffset) override;

    private:
        bool m_isRunning = false;

        Window m_window = Window();

        ImGuiController m_gui = ImGuiController();

        LightingWidget m_lightingWidget = LightingWidget("Lighting");
        ViewportWidget m_viewport       = ViewportWidget("Viewport");
        StatsWidget m_statsWidget       = StatsWidget("Statistics");

        std::unique_ptr<Scene> m_scene       = nullptr;
        std::unique_ptr<Renderer> m_renderer = nullptr;
    };
} // namespace gir
