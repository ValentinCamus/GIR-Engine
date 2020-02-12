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

    // Begin Debug =====================================================================================================

    Shader* shader = nullptr;
    Model* nanoSuit = nullptr;

    DebugCamera debugCamera({0.0f, 0.0f, 3.0f});

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // End Debug =======================================================================================================

    void Application::Setup()
    {
        m_viewport.Init(500, 500);

        shader = new Shader({
            {GL_VERTEX_SHADER, FileSystem::GetShadersDir() + "ModelDiffuse.vs.glsl"},
            {GL_FRAGMENT_SHADER, FileSystem::GetShadersDir() + "ModelDiffuse.fs.glsl"}
        });

        nanoSuit = ModelLoader::Load(FileSystem::GetAssetsDir() + "nanosuit.obj");

        glEnable(GL_DEPTH_TEST);

        // =============================================================================================================
        unsigned width  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned height = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

        Camera camera("Main camera", Mat4f(1.f), width, height);

        Mat4f transform(1.f);
        transform[3] = { 0.f, 0.f, -2.f, 1.f};

        m_scene = std::make_unique<Scene>(camera, std::vector<Light>(), std::vector<Entity> {Entity("test", nanoSuit, transform)});

        // m_renderer = std::make_unique<Renderer>(m_viewport.GetFramebuffer(), width, height);

    }

    void Application::Prepare()
    {

    }

    void Application::Draw()
    {
        m_viewport.GetFramebuffer()->Bind();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float aspectRatio = float(m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth()) /
                            float(m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight());

        glm::mat4 projection = glm::perspective(glm::radians(debugCamera.Zoom), aspectRatio, 0.1f, 100.0f);
        glm::mat4 view = debugCamera.GetViewMatrix();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

        shader->Bind();

        shader->SetUniform("uModel", model);
        shader->SetUniform("uView", view);
        shader->SetUniform("uProjection", projection);

        for(const Model::Element& element : nanoSuit->GetElements())
        {
            auto attr = element.material->GetAttribute(Material::EAttribute::Diffuse);

            if (attr.texture)
            {
                attr.texture->Bind(0);

                shader->SetUniform("uDiffuse", attr.texture->GetSlot());

                element.mesh->GetVAO().Bind();
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element.mesh->GetVAO().GetIndexBufferId());
                glDrawElements(GL_TRIANGLES, element.mesh->GetIndices().size(), GL_UNSIGNED_INT, nullptr);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                element.mesh->GetVAO().Unbind();

                attr.texture->Unbind();
            }
        }

        shader->Unbind();

        // m_renderer->Draw(m_scene.get());

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
        unsigned viewportWidth  = m_viewport.GetFramebuffer()->GetTexture(0)->GetWidth();
        unsigned viewportHeight = m_viewport.GetFramebuffer()->GetTexture(0)->GetHeight();

        m_scene->GetCamera().SetWidth(viewportWidth);
        m_scene->GetCamera().SetHeight(viewportHeight);

        // m_renderer->ResizeGBuffer(viewportWidth, viewportHeight);
    }

} // namespace gir