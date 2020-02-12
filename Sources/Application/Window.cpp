#include "Window.hpp"

namespace gir
{
    Window::Window(const char* name, unsigned int width, unsigned int height)
        : m_name(name)
    {
        Logger::Info("Creating GLFW window: \"{0}\", Size=[w={1}, h={2}]", name, width, height);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on MacOs.
#endif

        GIR_CHECK(glfwInit(), "Failed to initialize GLFW");
        m_window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), name, nullptr, nullptr);
        GIR_CHECK(m_window != nullptr, "Failed to create GLFW window");

        glfwMakeContextCurrent(m_window);
        GIR_CHECK(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");
    }

    Window::~Window()
    {
        GIR_ASSERT(IsValid(), "Window::Shutdown: Invalid window");
        glfwDestroyWindow(m_window);
        glfwTerminate();

        Logger::Info("Window: Shutdown");
    }

    void Window::PollEvents()
    {
        GIR_ASSERT(IsValid(), "Window::Shutdown: Invalid window");
        glfwPollEvents();
    }

    void Window::SwapBuffers()
    {
        GIR_ASSERT(IsValid(), "Window::Shutdown: Invalid window");
        glfwSwapBuffers(m_window);
    }

    void Window::SetupEventsCallback(WindowEventListener *listener)
    {
        GIR_ASSERT(IsValid(), "Window::Shutdown: Invalid window");
        GIR_ASSERT(listener != nullptr, "Window::SetupEventsCallback: Invalid parameter");

        glfwSetWindowUserPointer(m_window, listener);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
            auto listener = (WindowEventListener *)glfwGetWindowUserPointer(window);
            listener->OnWindowResize(width, height);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
            auto listener = (WindowEventListener *)glfwGetWindowUserPointer(window);
            listener->OnWindowClosed();
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scanCode, int action, int mods) {
            (void)mods;
            (void)scanCode;

            auto listener = (WindowEventListener *)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                    listener->OnKeyPressed(key);
                    break;
                case GLFW_RELEASE:
                    listener->OnKeyReleased(key);
                    break;
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
            (void)mods;

            auto listener = (WindowEventListener *)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                    listener->OnMousePressed(button);
                    break;
                case GLFW_RELEASE:
                    listener->OnMouseReleased(button);
                    break;
                default:
                    break;
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset) {
            auto listener = (WindowEventListener *)glfwGetWindowUserPointer(window);
            listener->OnMouseScrolled(xOffset, yOffset);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos) {
            auto listener = (WindowEventListener *)glfwGetWindowUserPointer(window);
            listener->OnMouseMoved(xPos, yPos);
        });
    }

} // namespace gir
