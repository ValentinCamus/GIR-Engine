
#include "Renderer.hpp"
#include "Engine/Scene/Scene.hpp"
#include "Engine/Manager/Manager.hpp"
#include "Engine/Mesh/Mesh.hpp"
#include "Engine/Light/Light.hpp"

namespace gir
{
    Renderer::Renderer(unsigned width, unsigned height) :
        m_shaderManager({{EShaderType::GBUFFER,
                          {{GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.vs.glsl"},
                           {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.fs.glsl"}}},
                         {EShaderType::DEFERRED_LIGHTING,
                          {{GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/CookTorrance.vs.glsl"},
                           {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/CookTorrance.fs.glsl"}}},
                         {EShaderType::DEBUG,
                          {{GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.vs.glsl"},
                           {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.fs.glsl"}}}}),
        m_GBuffer("GBuffer")
    {
        // Creating screen quad
        std::vector<Mesh::Vertex> vertices = {
            {{1.f, 1.f, 0.0f}, Vec3f(), {1.f, 1.f}},
            {{1.f, -1.f, 0.0f}, Vec3f(), {1.f, 0.f}},
            {{-1.f, -1.f, 0.0f}, Vec3f(), {0.f, 0.f}},
            {{-1.f, 1.f, 0.0f}, Vec3f(), {0.f, 1.f}},
        };

        std::vector<unsigned> indices = {1, 0, 2, 2, 0, 3};

        m_quad = std::make_unique<Mesh>("Deferred shading quad", std::move(indices), std::move(vertices));

        // Filling GBuffer with textures
        m_GBuffer.Bind();

        std::vector<GLuint> attachments {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};

        m_GBuffer.AttachTexture(std::make_unique<Texture2D>("position", GL_RGB32F, GL_RGB, GL_FLOAT), attachments[0]);
        m_GBuffer.AttachTexture(std::make_unique<Texture2D>("normalMetalness", GL_RGBA32F, GL_RGBA, GL_FLOAT),
                                attachments[1]);
        m_GBuffer.AttachTexture(std::make_unique<Texture2D>("albedoRoughness", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE),
                                attachments[2]);

        glDrawBuffers(attachments.size(), attachments.data());

        m_GBuffer.AttachRenderbuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);

        m_GBuffer.Resize(width, height);

        GIR_ASSERT(m_GBuffer.IsComplete(), "Incomplete GBuffer framebuffer");

        m_GBuffer.Unbind();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Renderer::Draw(Framebuffer* framebuffer, const Scene* scene)
    {
        auto* shader = m_shaderManager.GetShader(EShaderType::GBUFFER);

        shader->Bind();
        m_GBuffer.Bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& camera = scene->GetCamera();
        shader->SetUniform("vp", camera.GetProjectionMatrix() * camera.GetViewMatrix());

        for (const auto& entity : scene->GetEntities())
        {
            shader->SetUniform("model", entity->GetTransform());
            auto* model = entity->GetModel();

            for (int i = 0; i < static_cast<int>(model->MaterialCount()); ++i)
            {
                auto* material = model->GetMaterial(i);
                material->SetUniforms("material", shader, 0);

                for (const auto& mesh : model->GetMeshes(i))
                {
                    auto* vao = mesh->GetVertexArrayObject();
                    vao->Bind();
                    glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
                    vao->Unbind();
                }
                material->UnbindTextures();
            }
        }
        m_GBuffer.Unbind();

        shader->Unbind();

        switch (m_renderMode)
        {
            case ERenderMode::DEBUG:
            {
                shader = m_shaderManager.GetShader(EShaderType::DEBUG);

                shader->Bind();

                framebuffer->Bind();
                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);

                auto* vao = m_quad->GetVertexArrayObject();
                vao->Bind();

                auto* texture = m_GBuffer.GetTexture(2);
                texture->Bind(2);
                shader->SetUniform(texture->GetName(), 2);

                glDrawElements(GL_TRIANGLES, m_quad->GetIndices().size(), GL_UNSIGNED_INT, nullptr);

                m_GBuffer.GetTexture(2)->Unbind();

                glEnable(GL_DEPTH_TEST);

                vao->Unbind();
                framebuffer->Unbind();
                shader->Unbind();

                break;
            }
            case ERenderMode::DIRECT:
            {
                shader = m_shaderManager.GetShader(EShaderType::DEFERRED_LIGHTING);

                shader->Bind();

                framebuffer->Bind();
                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);

                auto* vao = m_quad->GetVertexArrayObject();
                vao->Bind();

                shader->SetUniform("cameraPosition", Vec3f(camera.GetTransform()[3]));

                const auto& lights = scene->GetLights();
                shader->SetUniform("lightCount", static_cast<unsigned>(lights.size()));

                for (int i = 0; i < static_cast<int>(lights.size()); ++i)
                    lights[i]->SetUniforms("lights[" + std::to_string(i) + "]", shader);

                for (int i = 0; i < m_GBuffer.TextureCount(); ++i)
                {
                    auto* texture = m_GBuffer.GetTexture(i);
                    texture->Bind(i);
                    shader->SetUniform(texture->GetName(), i);
                }

                glDrawElements(GL_TRIANGLES, m_quad->GetIndices().size(), GL_UNSIGNED_INT, nullptr);

                for (int i = 0; i < m_GBuffer.TextureCount(); ++i) { m_GBuffer.GetTexture(i)->Unbind(); }

                glEnable(GL_DEPTH_TEST);

                vao->Unbind();
                framebuffer->Unbind();
                shader->Unbind();

                break;
            }
            default:
            {
                Logger::Error("Invalid render mode");
                break;
            }
        }
    }

    void Renderer::ResizeGBuffer(unsigned width, unsigned height) { m_GBuffer.Resize(width, height); }

    void Renderer::SetRenderMode(ERenderMode mode) { m_renderMode = mode; }

} // namespace gir