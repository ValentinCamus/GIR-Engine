#include "Application.hpp"

#include <Engine/Shader/Shader.hpp>
#include <Engine/Mesh/VertexArrayObject.hpp>
#include <Engine/Manager/Manager.hpp>

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

    void Application::Setup()
    {
        m_viewport.Init(500, 500);

        std::vector<Vec3f> vertices = {
            {0.5f, 0.5f, 0.0f},   // top right
            {0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f}, // bottom left
            {-0.5f, 0.5f, 0.0f}   // top left
        };

        std::vector<Vec3f> colors = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};

        std::vector<unsigned> indices = {
            0,
            1,
            3, // first Triangle
            1,
            2,
            3 // second Triangle
        };

        Camera camera("Main camera", Mat4f(1.f), DEFAULT_APP_WIDTH, DEFAULT_APP_HEIGHT);

        Model* model = new Model("test");

        auto* mesh = Manager<Mesh>::Add(
            "test", nullptr, std::move(indices), std::move(vertices), std::move(colors), std::vector<Vec2f>(4));
        model->AddMesh(mesh);

        m_scene = std::make_unique<Scene>(camera, std::vector<Light>(), std::vector<Entity> {Entity("test", model)});

        m_renderer = std::make_unique<Renderer>();
    }

    void Application::Prepare() {}

    void Application::Draw()
    {
        m_viewport.GetFramebuffer()->Bind();
        m_renderer->Draw(m_scene.get());
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
        m_scene->GetCamera().SetWidth(width);
        m_scene->GetCamera().SetHeight(height);
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