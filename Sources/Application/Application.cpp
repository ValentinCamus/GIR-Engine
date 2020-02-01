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
        m_viewport.Init(500, 500);
    }

    void Application::Prepare()
    {

    }

    void Application::Draw()
    {
        m_viewport.GetFramebuffer()->Bind();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_viewport.GetFramebuffer()->Unbind();
    }

    void Application::ImGuiDraw()
    {
        m_viewport.Draw();
        m_lightingWidget.Draw();
        m_statsWidget.Draw();
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