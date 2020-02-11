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

    Shader* shader = nullptr;
    Model* nanoSuit = nullptr;

    DebugCamera camera({0.0f, 0.0f, 3.0f});

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void Application::Setup()
    {
        m_viewport.Init(500, 500);

        shader = new Shader({
            {GL_VERTEX_SHADER, FileSystem::GetShadersDir() + "Debug.vs.glsl"},
            {GL_FRAGMENT_SHADER, FileSystem::GetShadersDir() + "Debug.fs.glsl"}
        });

        nanoSuit = ModelLoader::Load(FileSystem::GetAssetsDir() + "nanosuit.obj");

        glEnable(GL_DEPTH_TEST);

        /*
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
        */
    }

    void Application::Prepare()
    {

    }

    void Application::Draw()
    {
        m_viewport.GetFramebuffer()->Bind();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // m_scene->GetCamera().SetWidth(m_viewport.GetFramebuffer()->GetTexture()->GetWidth());
        // m_scene->GetCamera().SetHeight(m_viewport.GetFramebuffer()->GetTexture()->GetHeight());

        float aspectRatio = float(m_viewport.GetFramebuffer()->GetTexture()->GetWidth()) /
                            float(m_viewport.GetFramebuffer()->GetTexture()->GetHeight());

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

        shader->Bind();

        shader->SetUniform("uModel", model);
        shader->SetUniform("uView", view);
        shader->SetUniform("uProjection", projection);

        for(Model::Element& element : nanoSuit->GetElements())
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

        // m_renderer->Draw(m_scene.get());

        shader->Unbind();

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

} // namespace gir