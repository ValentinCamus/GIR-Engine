#include "Application.hpp"

namespace gir
{
    Application::Application(const char* name, unsigned int width, unsigned int height)
    {
        Logger::Info("Creating GLFW window: \"{0}\", Dimension = [w={1}, h={2}]", name, width, height);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required by on MacOs.
#endif
        GIR_CHECK(glfwInit(), "Failed to initialize GLFW");
        m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        GIR_CHECK(m_window != nullptr, "Failed to create GLFW window");

        glfwMakeContextCurrent(m_window);
        GIR_CHECK(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to initiaze GLAD");

        glfwSetWindowUserPointer(m_window, this);

        Logger::Info("OpenGL renderer: Initialized");
        // Logger::Info("\tVendor: {0}", glGetString(GL_VENDOR));
        // Logger::Info("\tVersion: {0}", glGetString(GL_VERSION));
        // Logger::Info("\tRenderer: {0}", glGetString(GL_RENDERER));

        SetupEventsCallback();
        Setup();
    }

    void Application::Run()
    {
        m_isRunning = true;

        while (m_isRunning)
        {
            glfwPollEvents();

            Prepare();
            Draw();
            ImGuiDraw();

            glfwSwapBuffers(m_window);
        }
    }

    void Application::Stop()
    {
        if (m_window)
        {
            m_isRunning = false;

            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }

    void Application::SetupEventsCallback()
    {
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
        {
            auto app = (Application*) glfwGetWindowUserPointer(window);

            app->OnWindowResize(width, height);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
        {
            auto app = (Application*) glfwGetWindowUserPointer(window);

            app->OnWindowClosed();
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scanCode, int action, int mods)
        {
            (void) mods;
            (void) scanCode;

            auto app = (Application*) glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    app->OnKeyPressed(key);
                    break;
                }
                case GLFW_RELEASE:
                {
                    app->OnKeyReleased(key);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods)
        {
            (void) mods;

            auto app = (Application*) glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    app->OnMousePressed(button);
                    break;
                }
                case GLFW_RELEASE:
                {
                    app->OnMouseReleased(button);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset)
        {
            auto app = (Application*) glfwGetWindowUserPointer(window);

            app->OnMouseScrolled(xOffset, yOffset);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos)
        {
            auto app = (Application*) glfwGetWindowUserPointer(window);

            app->OnMouseMoved(xPos, yPos);
        });
    }

    void Application::Setup()
    {

    }

    void Application::Prepare()
    {

    }

    void Application::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Application::ImGuiDraw()
    {

    }

    void Application::OnWindowClosed()
    {
        Stop();
    }

    void Application::OnWindowResize(int width, int height)
    {
        (void) width;
        (void) height;
    }

    void Application::OnKeyPressed(int keyCode)
    {
        (void) keyCode;
    }

    void Application::OnKeyReleased(int keyCode)
    {
        (void) keyCode;
    }

    void Application::OnMousePressed(int button)
    {
        (void) button;
    }

    void Application::OnMouseReleased(int button)
    {
        (void) button;
    }

    void Application::OnMouseMoved(double xPos, double yPos)
    {
        (void) xPos;
        (void) yPos;
    }

    void Application::OnMouseScrolled(double xOffset, double yOffset)
    {
        (void) xOffset;
        (void) yOffset;
    }
}