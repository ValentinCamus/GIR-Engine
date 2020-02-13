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
        m_window = new Window(name, width, height);
        m_window->SetupEventsCallback(this);

        // Initialize the GUI
        m_gui = new ImGuiController(m_window->Get());
    }

    Application::~Application()
    {
        // Warning: Here, the destruction order is important.

        delete m_viewport;
        delete m_statsWidget;
        delete m_lightingWidget;
        delete m_gui; // Shutdown ImGui.
        delete m_window; // Shutdown GLFW and OpenGL.
    }
    void Application::Run()
    {
        m_isRunning = true;

        while (m_isRunning)
        {
            // Per-frame time logic
            auto currentTime = static_cast<float>(glfwGetTime());
            float deltaTime  = m_time - currentTime;
            m_time = currentTime;

            m_window->PollEvents();

            Prepare(deltaTime);
            Draw(deltaTime);

            m_gui->BeginFrame();
            ImGuiDraw(deltaTime);
            m_gui->EndFrame();

            m_window->SwapBuffers();
        }
    }

    void Application::Stop()
    {
        m_isRunning = false;
    }

    void Application::Setup()
    {
        // Link the input controller with the window system.
        m_input = std::make_unique<Input>(m_window->Get());

        // Create all the application widgets.
        m_statsWidget = new StatsWidget("Statistics");
        m_lightingWidget = new LightingWidget("Lighting");
        m_viewport = new ViewportWidget("Viewport", 500, 500);

        Model* nanoSuit = ModelLoader::Load(FileSystem::GetAssetsDir() + "nanosuit.obj");

        unsigned width  = m_viewport->GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned height = m_viewport->GetFramebuffer()->GetTexture(0)->GetHeight();

        Mat4f transform(1.f);
        transform[3] = {0.f, -7.5f, -20.f, 1.f};
        
        m_scene = std::make_unique<Scene>(
            Camera("MainCamera", Mat4f(1.f), width, height),
            std::vector<Light*>(),
            std::vector<Entity> {
                Entity("NanoSuit", nanoSuit, transform)
            }
        );

        m_cameraController = std::make_unique<CameraController>(&m_scene->GetCamera());
        m_renderer = std::make_unique<Renderer>(width, height);
    }

    void Application::Prepare(float deltaTime)
    {
        // Step 1: Camera's inputs
        if (m_input->IsKeyPressed(GLFW_KEY_W)) m_cameraController->MoveForward(deltaTime);
        if (m_input->IsKeyPressed(GLFW_KEY_S)) m_cameraController->MoveBackward(deltaTime);
        if (m_input->IsKeyPressed(GLFW_KEY_D)) m_cameraController->MoveRight(deltaTime);
        if (m_input->IsKeyPressed(GLFW_KEY_A)) m_cameraController->MoveLeft(deltaTime);
        if (m_input->IsKeyPressed(GLFW_KEY_Q)) m_cameraController->MoveUp(deltaTime);
        if (m_input->IsKeyPressed(GLFW_KEY_E)) m_cameraController->MoveDown(deltaTime);


        if (m_input->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        {
            m_cameraController->SetMousePos(m_input->GetMouseX(), m_input->GetMouseY());
        }

        // Step 2: The camera and renderer's GBuffer dimensions depends on the viewport and not the window.
        Camera& camera = m_scene->GetCamera();

        unsigned viewportWidth  = m_viewport->GetWidth();
        unsigned viewportHeight = m_viewport->GetHeight();

        if (camera.GetWidth() != viewportWidth || camera.GetHeight() != viewportHeight)
        {
            camera.SetWidth(viewportWidth);
            camera.SetHeight(viewportHeight);

            m_renderer->ResizeGBuffer(viewportWidth, viewportHeight);
        }
    }

    void Application::Draw(float deltaTime)
    {
        m_renderer->Draw(m_scene.get(), m_viewport->GetFramebuffer());
    }

    void Application::ImGuiDraw(float deltaTime)
    {
        m_viewport->Draw();
        m_lightingWidget->Draw();
        m_statsWidget->Draw();
    }

    void Application::OnWindowClosed()
    {
        Stop();
    }

    void Application::OnMouseMoved(double xPos, double yPos)
    {
        if (m_scene)
        {
            if (m_input->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
            {
                m_cameraController->LookAt(static_cast<float>(xPos), static_cast<float>(yPos));
            }
        }
    }

    void Application::OnMouseScrolled(double xOffset, double yOffset)
    {
        if (m_scene)
        {
            m_cameraController->Zoom(static_cast<float>(yOffset));
        }
    }

} // namespace gir