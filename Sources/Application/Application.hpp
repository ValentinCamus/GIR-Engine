#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Core.hpp>

#define DEFAULT_APP_NAME    "Application"
#define DEFAULT_APP_WIDTH   800
#define DEFAULT_APP_HEIGHT  600

namespace gir
{
    class Application
    {
    public:
        /// Default constructor.
        explicit Application(const char* name    = DEFAULT_APP_NAME,
                             unsigned    width   = DEFAULT_APP_WIDTH,
                             unsigned    height  = DEFAULT_APP_HEIGHT);

        /// Default destructor.
        virtual ~Application() = default;

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
        virtual void OnWindowClosed();

        /// Event called when the size of the window has changed.
        virtual void OnWindowResize(int width, int height);

        /// Event called when a key is pressed.
        virtual void OnKeyPressed(int keyCode);

        /// Event called when a key is released.
        virtual void OnKeyReleased(int keyCode);

        /// Event called when a mouse button is pressed.
        virtual void OnMousePressed(int button);

        /// Event called when a mouse button is released.
        virtual void OnMouseReleased(int button);

        /// Event called when the mouse position changed.
        virtual void OnMouseMoved(double xPos, double yPos);

        /// Event called when a scrolling device is used.
        virtual void OnMouseScrolled(double xOffset, double yOffset);

    private:
        /// Setup glfw events callback.
        void SetupEventsCallback();

    private:
        bool m_isRunning = false;

        GLFWwindow* m_window = nullptr;
    };
}


