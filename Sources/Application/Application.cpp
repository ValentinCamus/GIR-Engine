#include "Application.hpp"

#include <Engine/Shader/Shader.hpp>
#include <Engine/Mesh/VertexArrayObject.hpp>
#include <Engine/Manager/Manager.hpp>
#include <IO/Loader/TextureLoader.hpp>
#include <Engine/Texture/Texture2D.hpp>
#include <IO/FileSystem/FileSystem.hpp>
#include <IO/Loader/ModelLoader.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Camera/CameraDebug.hpp>

namespace gir
{
    Application::Application(const char* name, unsigned int width, unsigned int height)
    {
        // Initialize GLFW window
        m_window.Init(name, width, height);
        m_window.SetupEventsCallback(this);

        // Initialize the GUI
        m_gui.Init(m_window.Get());

        // Link the input controller with the window system.
        m_input.Init(m_window.Get());
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

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // End Debug =======================================================================================================

    void Application::Setup()
    {
        m_viewport.Init(500, 500);

        Model* nanoSuit = ModelLoader::Load(FileSystem::GetAssetsDir() + "nanosuit.obj");

        unsigned width  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned height = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

        Camera camera("Main camera", Mat4f(1.f), width, height);

        Mat4f transform(1.f);
        transform[3] = {0.f, -7.5f, -20.f, 1.f};

        m_scene = std::make_unique<Scene>(
            camera, std::vector<Light*>(), std::vector<Entity> {Entity("test", nanoSuit, transform)});

        m_renderer = std::make_unique<Renderer>(m_viewport.GetFramebuffer(), width, height);
    }

    void Application::Prepare() {}

    void Application::Draw() { m_renderer->Draw(m_scene.get()); }

    void Application::ImGuiDraw()
    {
        m_viewport.Draw();
        m_lightingWidget.Draw();
        m_statsWidget.Draw();
    }

    void Application::OnWindowClosed() { Stop(); }

    void Application::OnWindowResize(int width, int height)
    {
        unsigned viewportWidth  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned viewportHeight = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

        Logger::Info(viewportWidth);
        Logger::Info(viewportHeight);
        m_scene->GetCamera().SetWidth(viewportWidth);
        m_scene->GetCamera().SetHeight(viewportHeight);

        m_renderer->ResizeGBuffer(viewportWidth, viewportHeight);
    }

} // namespace gir