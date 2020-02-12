#include "Renderer.hpp"
#include "Engine/Scene/Scene.hpp"
#include "Engine/Manager/Manager.hpp"
#include "Engine/Mesh/Mesh.hpp"

namespace gir
{
    Renderer::Renderer(Framebuffer* defaultFramebuffer, unsigned width, unsigned height) :
        m_shaderManager({{EShaderType::DEBUG,
                          {{GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.vs.glsl"},
                           {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.fs.glsl"}}},
                         {EShaderType::GBUFFER,
                          {{GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.vs.glsl"},
                           {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.fs.glsl"}}}}),
        m_defaultFramebuffer(defaultFramebuffer),
        m_GBuffer("GBuffer")
    {
        // Creating screen quad
        std::vector<Vec3f> vertices = {
            {0.5f, 0.5f, 0.0f},   // top right
            {0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f}, // bottom left
            {-0.5f, 0.5f, 0.0f}   // top left
        };

        std::vector<unsigned> indices = {
            0,
            1,
            3, // first Triangle
            1,
            2,
            3 // second Triangle
        };

        std::vector<Vec2f> textureCoordinates = {{1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, {0.f, 1.f}};

        unsigned size = static_cast<unsigned>(vertices.size());
        m_quad        = Manager<Mesh>::Add("Deferred shading quad",
                                    nullptr,
                                    std::move(indices),
                                    std::move(vertices),
                                    std::vector<Vec3f>(size),
                                    std::move(textureCoordinates));

        // Filling GBuffer with textures
        m_GBuffer.Bind();

        m_GBuffer.AttachRenderbuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        m_GBuffer.Resize(width, height);

        std::vector<GLuint> attachments {GL_COLOR_ATTACHMENT2};

        Texture2D* texture; /* = Manager<Texture2D>::Add("Positions", GL_RGB32F, GL_FLOAT);
         texture->Bind();
         texture->Allocate(width, height);
         texture->Unbind();
         m_GBuffer.AttachTexture(texture, GL_COLOR_ATTACHMENT0);

         texture = Manager<Texture2D>::Add("Normals", GL_RGB32F, GL_FLOAT);
         texture->Bind();
         texture->Allocate(width, height);
         texture->Unbind();
         m_GBuffer.AttachTexture(texture, GL_COLOR_ATTACHMENT1);*/

        texture = Manager<Texture2D>::Add("Diffuse colors", GL_RGB, GL_UNSIGNED_BYTE);
        texture->Bind();
        texture->Allocate(width, height);
        texture->Unbind();
        m_GBuffer.AttachTexture(texture, GL_COLOR_ATTACHMENT2);

        /*texture = Manager<Texture2D>::Add("Specular colors", GL_RGB, GL_UNSIGNED_BYTE);
        texture->Bind();
        texture->Allocate(width, height);
        texture->Unbind();
        m_GBuffer.AttachTexture(texture, GL_COLOR_ATTACHMENT3);

        texture = Manager<Texture2D>::Add("Specular parameters", GL_RG16F, GL_FLOAT);
        texture->Bind();
        texture->Allocate(width, height);
        texture->Unbind();
        m_GBuffer.AttachTexture(texture, GL_COLOR_ATTACHMENT4);*/

        glDrawBuffers(attachments.size(), attachments.data());

        GIR_ASSERT(m_GBuffer.IsComplete(), "Incomplete GBuffer framebuffer");

        m_GBuffer.Unbind();

        glEnable(GL_CULL_FACE);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Renderer::Draw(const Scene* scene)
    {
        switch (m_renderMode)
        {
            case RenderMode::DEBUG:
            {
                auto* shader = m_shaderManager.GetShader(EShaderType::GBUFFER);

                shader->Bind();
                m_defaultFramebuffer->Unbind();
                m_GBuffer.Bind();

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->SetUniform("vp", scene->GetCamera().GetProjectionMatrix() * scene->GetCamera().GetViewMatrix());

                for (const auto& entity : scene->GetEntities())
                {
                    shader->SetUniform("model", entity.GetTransform());
                    auto* model = entity.GetModel();

                    for (int i = 0; i < model->MaterialCount(); ++i)
                    {
                        for (const auto& mesh : model->GetMeshes(i))
                        {
                            auto* vao = mesh->GetVertexArrayObject();
                            vao->Bind();
                            glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
                            vao->Unbind();
                        }
                    }
                }
                m_GBuffer.Unbind();
                shader->Unbind();

                shader = m_shaderManager.GetShader(EShaderType::DEBUG);
                shader->Bind();
                m_defaultFramebuffer->Bind();
                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);

                auto* vao = m_quad->GetVertexArrayObject();
                vao->Bind();

                // const char* uniforms[5] = {"positions", "normals", "diffuseColor", "specularColor",
                // "specularParameters"};
                const char* uniforms[1] = {"diffuseColor"};

                for (int i = 0; i < m_GBuffer.TextureCount(); ++i)
                {
                    m_GBuffer.GetTexture(i)->Bind(i);
                    shader->SetUniform(uniforms[i], i);
                }

                glDrawElements(GL_TRIANGLES, m_quad->Size(), GL_UNSIGNED_INT, 0);

                for (int i = 0; i < m_GBuffer.TextureCount(); ++i) { m_GBuffer.GetTexture(i)->Unbind(); }

                glEnable(GL_DEPTH_TEST);
                vao->Unbind();
                shader->Unbind();
            }
            break;

            case RenderMode::RSM:
                break;

            default:
                Logger::Error("Invalid render mode");
                break;
        }
    }

    void Renderer::ResizeGBuffer(unsigned width, unsigned height) { m_GBuffer.Resize(width, height); }

    void Renderer::SetRenderMode(RenderMode mode) { m_renderMode = mode; }

} // namespace gir