#include "Application.hpp"

#include <IO/Loader/ModelLoader.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Light/DirectionnalLight.hpp>
#include <Engine/Light/SpotLight.hpp>
#include <Engine/Light/PointLight.hpp>

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
            // Per-frame time logic
            auto currentTime = static_cast<float>(glfwGetTime());
            float deltaTime  = m_time - currentTime;
            m_time           = currentTime;

            m_window.PollEvents();

            Prepare(deltaTime);
            Draw(deltaTime);

            m_gui.BeginFrame();
            ImGuiDraw(deltaTime);
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

        Model* sponza = ModelLoader::Load(FileSystem::GetAssetsDir() + "sponza.obj");

        unsigned width  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned height = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

        Mat4f cameraTransform(1.f);
        cameraTransform[3] = {0.f, 10.f, 0.f, 1.f};
        Camera camera("Main camera", cameraTransform, width, height);

        Mat4f entityTransform(0.025f);
        entityTransform[3] = {0.f, 0.f, 0.f, 1.f};

        Mat4f lightTransform(glm::rotate(-PI / 3, Vec3f(1.f, 0.f, 0.f)));

        std::vector<std::unique_ptr<Light>> lights;
        lightTransform[3] = {0.f, 6.5f, 0.f, 1.f};
        lights.emplace_back(std::make_unique<PointLight>("Pointlight", lightTransform, Vec3f(60.f, 40.f, 30.f)));

        lightTransform[3] = {0.f, 55.f, 0.f, 1.f};
        lights.emplace_back(std::make_unique<DirectionnalLight>("Sunlight", lightTransform, Vec3f(0.8f, 0.6f, 0.45f)));

        lightTransform    = glm::rotate(-PI / 3, Vec3f(1.f, 0.f, 0.f)) * glm::rotate(-PI / 2, Vec3f(0.f, 1.f, 0.f));
        lightTransform[3] = {18.f, 4.5f, 0.f, 1.f};
        lights.emplace_back(
            std::make_unique<SpotLight>("Spotlight", lightTransform, Vec3f(28.f, 20.f, 15.f), 0.5f * PI / 4, PI / 4));


        m_scene = std::make_unique<Scene>(
            camera, std::move(lights), std::vector<Entity> {Entity("Scene", sponza, entityTransform)});

        m_renderer = std::make_unique<Renderer>(m_viewport.GetFramebuffer(), width, height);
    }

    void Application::Prepare(float deltaTime)
    {
        m_cameraController.SetCamera(&m_scene->GetCamera());

        bool dragging = m_input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1);
        if (dragging && !m_cameraController.isMouseDragged())
            m_cameraController.SetMousePos(m_input.GetMouseX(), m_input.GetMouseY());

        m_cameraController.SetMouseDragged(dragging);

        if (m_input.IsKeyPressed(GLFW_KEY_W)) m_cameraController.MoveForward(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_S)) m_cameraController.MoveBackward(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_D)) m_cameraController.MoveRight(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_A)) m_cameraController.MoveLeft(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_Q)) m_cameraController.MoveUp(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_E)) m_cameraController.MoveDown(deltaTime);

        if (m_input.IsKeyPressed(GLFW_KEY_F5))
        {
            unsigned width  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
            unsigned height = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();
            m_renderer      = std::make_unique<Renderer>(m_viewport.GetFramebuffer(), width, height);
        }
    }

    void Application::Draw(float deltaTime)
    {
        unsigned viewportWidth  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned viewportHeight = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

        Camera& camera = m_scene->GetCamera();
        if (camera.GetWidth() != viewportWidth || camera.GetHeight() != viewportHeight)
        {
            camera.SetWidth(viewportWidth);
            camera.SetHeight(viewportHeight);

            m_renderer->ResizeGBuffer(viewportWidth, viewportHeight);
        }

        m_renderer->SetRenderMode(static_cast<ERenderMode>(m_lightingWidget.GetLightingMode()));

        m_renderer->Draw(m_scene.get());
    }

    void Application::ImGuiDraw(float deltaTime)
    {
        m_viewport.Draw();
        m_lightingWidget.Draw();
        m_statsWidget.Draw();
    }

    void Application::OnWindowClosed() { Stop(); }

    void Application::OnMouseMoved(double xPos, double yPos)
    {
        if (m_scene) { m_cameraController.DragMouse(static_cast<float>(xPos), static_cast<float>(yPos)); }
    }

    void Application::OnMouseScrolled(double xOffset, double yOffset)
    {
        if (m_scene)
        {
            m_cameraController.SetCamera(&m_scene->GetCamera());
            m_cameraController.Zoom(static_cast<float>(yOffset));
        }
    }

} // namespace gir