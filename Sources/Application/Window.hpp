#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Application/WindowEventListener.hpp>

#include <Core/Core.hpp>

namespace gir
{
    class Window
    {
    public:
        /// Initialize and create the window.
        void Init(const char* name, unsigned int width, unsigned int height);

        /// Destroy the window.
        void Shutdown();

        /// Bind the GLFW's events to the WindowEventListener's events.
        void SetupEventsCallback(WindowEventListener* listener);

        /// This function processes only those events that are already in the event queue and then returns immediately.
        /// Processing events will cause the window and input callbacks associated with those events to be called.
        void PollEvents();

        /// This function swaps the front and back buffers of the specified window when rendering with OpenGL.
        void SwapBuffers();

        /// Check if the glfw window instance is initialized.
        inline bool IsValid() const { return m_window != nullptr; }

        /// @return: the native window.
        inline GLFWwindow* Get() const { return m_window; }

        /// @return: the window's name/title.
        inline const char* GetName() const { return m_name; }

        /// @return: the time elapsed since the window was initialized.
        inline double GetTime() const { return glfwGetTime(); }

    private:
        /// Window's title.
        const char* m_name = "Untitled";

        GLFWwindow* m_window = nullptr;
    };
} // namespace gir
