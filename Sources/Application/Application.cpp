#include "Application.hpp"

#include <Engine/Shader/Shader.hpp>
#include <Engine/Mesh/VertexArrayObject.hpp>

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

    void Application::Stop() { m_isRunning = false; }

    Shader* shader = nullptr;
    VertexArrayObject* vao = nullptr;

    void Application::Setup()
    {
        m_viewport.Init(500, 500);

        shader = new Shader({
            {GL_VERTEX_SHADER, PROJECT_SOURCE_DIR"/Shaders/Debug.vs.glsl"},
            {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR"/Shaders/Debug.fs.glsl"}
        });

        std::vector<Vec3f> vertices = {
            {0.5f,  0.5f, 0.0f},  // top right
            {0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f},  // bottom left
            {-0.5f,  0.5f, 0.0f}   // top left
        };

        std::vector<float> colors = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
        };

        std::vector<unsigned> indices = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
        };

        vao = new VertexArrayObject();

        vao->Bind();
        vao->AddFloatBuffer(vertices, 3);
        vao->AddFloatBuffer(colors, 3);
        vao->AddIndexBuffer(indices);
        vao->Unbind();
    }

    void Application::Prepare() {}

    void Application::Draw()
    {
        m_viewport.GetFramebuffer()->Bind();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->Bind();

        static float grad = 0.01;

        shader->SetUniform("uColor", {0, grad, 1, 1});

        if (grad > 1.0) grad = 0.01;
        else grad += 0.001;

        vao->Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        vao->Unbind();

        shader->Unbind();

        m_viewport.GetFramebuffer()->Unbind();
    }

    void Application::ImGuiDraw()
    {
        m_viewport.Draw();
        m_lightingWidget.Draw();
        m_statsWidget.Draw();
    }

    void Application::OnWindowClosed() { Stop(); }

    void Application::OnWindowResize(int width, int height)
    {
        (void)width;
        (void)height;
    }

    void Application::OnKeyPressed(int keyCode) { (void)keyCode; }

    void Application::OnKeyReleased(int keyCode) { (void)keyCode; }

    void Application::OnMousePressed(int button) { (void)button; }

    void Application::OnMouseReleased(int button) { (void)button; }

    void Application::OnMouseMoved(double xPos, double yPos)
    {
        (void)xPos;
        (void)yPos;
    }

    void Application::OnMouseScrolled(double xOffset, double yOffset)
    {
        (void)xOffset;
        (void)yOffset;
    }
} // namespace gir