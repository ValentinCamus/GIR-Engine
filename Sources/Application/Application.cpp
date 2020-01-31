#include "Application.hpp"

namespace gir
{
    Application::Application(const char* name, unsigned int width, unsigned int height)
    {
        // Initialize GLFW window
        m_window.Init(name, width, height);
        m_window.SetupEventsCallback(this);

        // Initialize the GUI
        m_gui.Init(m_window.Get());

        Setup();
    }

    void Application::Run()
    {
        m_isRunning = true;

        while (m_isRunning)
        {
            m_window.PollEvents();

            Prepare();
            Draw();

            m_gui.BeginFrame();
            ImGuiDraw();
            m_gui.EndFrame();

            m_window.SwapBuffers();
        }

        m_gui.Shutdown();
        m_window.Shutdown();
    }

    void Application::Stop()
    {
        m_isRunning = false;
    }

    void Application::Setup()
    {
        m_viewport0.Init(500, 500);
        m_viewport1.Init(500, 500);
        m_viewport2.Init(500, 500);
    }

    void Application::Prepare()
    {

    }

    void Application::Draw()
    {
        m_viewport0.GetFramebuffer()->Bind();
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_viewport0.GetFramebuffer()->Unbind();

        m_viewport1.GetFramebuffer()->Bind();
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_viewport1.GetFramebuffer()->Unbind();

        m_viewport2.GetFramebuffer()->Bind();
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_viewport2.GetFramebuffer()->Unbind();
    }

    void Application::ImGuiDraw()
    {
        m_viewport0.Draw();
        m_viewport1.Draw();
        m_viewport2.Draw();
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