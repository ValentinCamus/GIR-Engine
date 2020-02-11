#include "Application.hpp"

#include <Engine/Shader/Shader.hpp>
#include <Engine/Mesh/VertexArrayObject.hpp>
#include <IO/Loader/TextureLoader.hpp>
#include <Engine/Texture/Texture2D.hpp>
#include <IO/FileSystem/FileSystem.hpp>
#include <IO/Loader/ModelLoader.hpp>
#include <Engine/Camera/Camera.hpp>

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

    void Application::Setup()
    {
        m_viewport.Init(500, 500);

        shader = new Shader({
            {GL_VERTEX_SHADER, FileSystem::GetShadersDir() + "Debug.vs.glsl"},
            {GL_FRAGMENT_SHADER, FileSystem::GetShadersDir() + "Debug.fs.glsl"}
        });

        nanoSuit = ModelLoader::Load(FileSystem::GetAssetsDir() + "nanosuit.obj");
    }

    void Application::Prepare() {}

    void Application::Draw()
    {
        m_viewport.GetFramebuffer()->Bind();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float aspectRatio = (float)m_viewport.GetFramebuffer()->GetTexture()->GetWidth() / (float)m_viewport.GetFramebuffer()->GetTexture()->GetHeight();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
        glm::mat4 view = Mat4f(1.0f);

        shader->SetUniform("uProjection", projection);
        shader->SetUniform("uView", view);

        shader->Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        shader->SetUniform("uModel", model);

        for(Model::Element& element : nanoSuit->GetElements())
        {
            auto attr = element.material->GetAttribute(Material::EAttribute::Diffuse);

            if (attr.texture)
            {
                attr.texture->Bind(0);

                shader->SetUniform("uDiffuse", attr.texture->GetSlot());

                element.mesh.GetVAO().Bind();
                glDrawElements(GL_TRIANGLES, element.mesh.GetIndices().size(), GL_UNSIGNED_INT, 0);
                element.mesh.GetVAO().Unbind();

                attr.texture->Unbind();
            }
        }

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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

} // namespace gir