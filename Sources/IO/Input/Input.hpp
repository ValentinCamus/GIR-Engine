#pragma once

#include <GLFW/glfw3.h>

#include <Core/Core.hpp>

namespace gir
{
    class Input
    {
    public:
        void Init(GLFWwindow* window);

        bool IsKeyPressed(int keyCode);

        bool IsMouseButtonPressed(int button);

        Vec2f GetMousePosition();

        float GetMouseX();

        float GetMouseY();

    private:
        GLFWwindow* m_window = nullptr;
    };
}



