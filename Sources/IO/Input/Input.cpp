#include "Input.hpp"

namespace gir
{
    Input::Input(GLFWwindow *window)
        : m_window(window)
    {

    }

    bool Input::IsKeyPressed(int keyCode)
    {
        if (!m_window) return false;

        auto state = glfwGetKey(m_window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        if (!m_window) return false;

        auto state = glfwGetMouseButton(m_window, button);
        return state == GLFW_PRESS;
    }

    Vec2f Input::GetMousePosition()
    {
        if (!m_window) return {0.0f, 0.0f};

        double xPos, yPos;
        glfwGetCursorPos(m_window, &xPos, &yPos);

        return { (float) xPos, (float) yPos };
    }

    float Input::GetMouseX()
    {
        if (!m_window) return 0.0f;

        Vec2f position = GetMousePosition();
        return position.x;
    }

    float Input::GetMouseY()
    {
        if (!m_window) return 0.0f;

        Vec2f position = GetMousePosition();
        return position.y;
    }
}