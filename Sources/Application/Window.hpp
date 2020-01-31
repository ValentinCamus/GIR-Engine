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
        void Init(const char* name, unsigned int width, unsigned int height);
        void Shutdown();

        void SetupEventsCallback(WindowEventListener* listener);

        void PollEvents();

        void SwapBuffers();

        inline bool IsValid() const { return m_window != nullptr; }

        inline GLFWwindow* Get() const { return m_window; }

        inline const char* GetName() const { return m_name; }

        inline const glm::vec2& GetSize() const { return m_size; }

    private:
        const char* m_name = "Untitled";
        glm::vec2 m_size = {0.0f, 0.0f};

        GLFWwindow* m_window = nullptr;
    };
}



