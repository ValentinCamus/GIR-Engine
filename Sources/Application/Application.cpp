#include "Application.hpp"

#include <IO/FileSystem/FileSystem.hpp>
#include <IO/Loader/ModelLoader.hpp>
#include <IO/Loader/SceneLoader.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Light/DirectionalLight.hpp>
#include <Engine/Light/SpotLight.hpp>
#include <Engine/Light/PointLight.hpp>

#include <IO/Saver/ImageWriter.hpp>

#define INITIAL_VIEWPORT_WIDTH 500
#define INITIAL_VIEWPORT_HEIGHT 500

namespace gir
{
    Application::Application(const char* name, unsigned int width, unsigned int height)
    {
        // Initialize GLFW window
        m_window.Init(name, width, height);
        m_window.SetupEventsCallback(this);
    }

    void Application::Run()
    {
        m_isRunning = true;

        m_gui.Init(m_window.Get());
        m_input.Init(m_window.Get());

        while (m_isRunning)
        {
            // Per-frame time logic
            auto currentTime = m_window.GetTime();
            auto deltaTime   = float(m_time - currentTime);
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
        m_viewport.Init(INITIAL_VIEWPORT_WIDTH, INITIAL_VIEWPORT_HEIGHT);

        m_scene    = SceneLoader::Load(FileSystem::GetProjectDir() + "/Scenes/Sponza.json");
        m_renderer = std::make_unique<Renderer>(static_cast<ERenderMode>(m_lightingWidget.GetLightingMode()),
                                                INITIAL_VIEWPORT_WIDTH,
                                                INITIAL_VIEWPORT_HEIGHT);
    }

    void Application::Shutdown() { m_viewport.Shutdown(); }

    void Application::Prepare(float deltaTime)
    {
        m_cameraController.SetCamera(&m_scene->GetCamera());

        bool dragging = m_input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE);
        if (dragging && !m_cameraController.isMouseDragged())
            m_cameraController.SetMousePosition(m_input.GetMouseX(), m_input.GetMouseY());

        m_cameraController.SetMouseDragged(dragging);

        if (m_input.IsKeyPressed(GLFW_KEY_W)) m_cameraController.MoveForward(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_S)) m_cameraController.MoveBackward(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_D)) m_cameraController.MoveRight(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_A)) m_cameraController.MoveLeft(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_Q)) m_cameraController.MoveUp(deltaTime);
        if (m_input.IsKeyPressed(GLFW_KEY_E)) m_cameraController.MoveDown(deltaTime);

        // Reload shaders
        if (m_input.IsKeyPressed(GLFW_KEY_F5))
        {
            unsigned width  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
            unsigned height = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

            m_renderer =
                std::make_unique<Renderer>(static_cast<ERenderMode>(m_lightingWidget.GetLightingMode()), width, height);
        }

        if (m_input.IsKeyPressed(GLFW_KEY_F6))
        {
            Framebuffer* framebuffer = m_viewport.GetFramebuffer();
            framebuffer->Bind();
            ImageWriter::Save(framebuffer, false);
            framebuffer->Unbind();
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

        m_renderer->Draw(m_viewport.GetFramebuffer(), m_scene.get());
    }

    void Application::ImGuiDraw(float deltaTime)
    {
        const Camera& camera              = m_scene->GetCamera();
        SceneComponent* selectedComponent = m_sceneWidget.GetSelectedComponent();

        m_sceneWidget.SetScene(m_scene.get());
        m_transformEditor.SetSceneComponent(selectedComponent);
        m_lightingWidget.SetLight(dynamic_cast<Light*>(selectedComponent));
        m_viewport.DrawGizmo(camera.GetProjectionMatrix(), camera.GetViewMatrix(), selectedComponent);

        m_viewport.Draw();
        m_lightingWidget.Draw();
        m_statsWidget.Draw();
        m_transformEditor.Draw();
        m_sceneWidget.Draw();
    }

    void Application::OnWindowClosed() { Stop(); }

    void Application::OnMouseMoved(double xPos, double yPos)
    {
        if (m_scene)
        {
            if (m_input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_3))
            {
                m_cameraController.SetCamera(&m_scene->GetCamera());
                m_cameraController.DragMouse(static_cast<float>(xPos), static_cast<float>(yPos));
            }
        }
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