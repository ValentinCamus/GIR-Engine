#include "Input.hpp"

namespace gir
{
    void Input::Init(GLFWwindow *window)
    {
        m_window = window;
        Logger::Info("Input mode: GLFW input system");
        Logger::Warn("GIR Engine supports only US keyboard binding (aka QWERTY)");
    }

    bool Input::IsKeyPressed(int keyCode)
    {
        auto state = glfwGetKey(m_window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        auto state = glfwGetMouseButton(m_window, button);
        return state == GLFW_PRESS;
    }

    Vec2f Input::GetMousePosition()
    {
        double xPos, yPos;
        glfwGetCursorPos(m_window, &xPos, &yPos);

        return { (float) xPos, (float) yPos };
    }

    float Input::GetMouseX()
    {
        Vec2f position = GetMousePosition();
        return position.x;
    }

    float Input::GetMouseY()
    {
        Vec2f position = GetMousePosition();
        return position.y;
    }
}