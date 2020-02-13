
#include "Renderer.hpp"
#include "Engine/Scene/Scene.hpp"
#include "Engine/Manager/Manager.hpp"
#include "Engine/Mesh/Mesh.hpp"

#include "Engine/Renderer/Quad.hpp"

#define GL_CHECK_ERROR()                                            \
    {                                                               \
        GLenum error;                                               \
        while ((error = glGetError()) != GL_NO_ERROR)               \
        {                                                           \
            std::string errorMessage;                               \
            switch (error)                                          \
            {                                                       \
                case GL_INVALID_ENUM:                               \
                    errorMessage = "Invalid enum";                  \
                    break;                                          \
                case GL_INVALID_VALUE:                              \
                    errorMessage = "Invalid value";                 \
                    break;                                          \
                case GL_INVALID_OPERATION:                          \
                    errorMessage = "Invalid operation";             \
                    break;                                          \
                case GL_INVALID_FRAMEBUFFER_OPERATION:              \
                    errorMessage = "Invalid framebuffer operation"; \
                    break;                                          \
                default:                                            \
                    errorMessage = "Unknown OpenGL error";          \
            }                                                       \
            Logger::Error(errorMessage);                            \
        }                                                           \
    }

namespace gir
{
    Renderer::Renderer(unsigned width, unsigned height) :
        m_shaderManager {},
        m_GBuffer("GBuffer")
    {
        m_shaderManager = ShaderManager({
            {
                EShaderType::DEBUG,
                {
                    {GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.vs.glsl"},
                    {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.fs.glsl"}
                }
            },
            {
                EShaderType::GBUFFER,
                {
                    {GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.vs.glsl"},
                    {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.fs.glsl"}
                }
            }
        });

        // Creating screen quad
        m_quad = Quad::Create("Deferred Shading Quad");

        InitializeGBuffer(width, height);

        glEnable(GL_CULL_FACE);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Renderer::Draw(const Scene *scene, Framebuffer* framebuffer)
    {
        switch (m_renderMode)
        {
            case ERenderMode::DEBUG:
            {
                GBufferDraw(scene);

                auto* shader = m_shaderManager.GetShader(EShaderType::DEBUG);
                auto* vao = m_quad->GetVertexArrayObject();

                if(framebuffer) framebuffer->Bind();
                shader->Bind();
                vao->Bind();

                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);

                const char* uniforms[5] = {
                    "positions",
                    "normals",
                    "diffuseColor",
                    "specularColor",
                    "specularParameters"
                };

                for (int i = 0; i < static_cast<int>(m_GBuffer.TextureCount()); ++i)
                {
                    m_GBuffer.GetTexture(i)->Bind(i);
                    shader->SetUniform(uniforms[i], i);
                }

                glDrawElements(GL_TRIANGLES, m_quad->GetIndices().size(), GL_UNSIGNED_INT, nullptr);

                for (int i = 0; i < static_cast<int>(m_GBuffer.TextureCount()); ++i)
                {
                    m_GBuffer.GetTexture(i)->Unbind();
                }

                glEnable(GL_DEPTH_TEST);

                vao->Unbind();
                shader->Unbind();
                if(framebuffer) framebuffer->Unbind();

                break;
            }
            case ERenderMode::RSM:
            {
                break;
            }
            default:
            {
                Logger::Error("Invalid render mode");
                break;
            }
        }
        GL_CHECK_ERROR()
    }

    void Renderer::InitializeGBuffer(unsigned width, unsigned height)
    {
        // Filling GBuffer with textures
        m_GBuffer.Bind();

        Texture2D* texture = Manager<Texture2D>::Add("Positions", GL_RGB32F, GL_RGB, GL_FLOAT);
        m_GBuffer.AttachTexture(texture, GBUFFER_ATTACHMENTS[0]);

        texture = Manager<Texture2D>::Add("Normals", GL_RGB32F, GL_RGB, GL_FLOAT);
        m_GBuffer.AttachTexture(texture, GBUFFER_ATTACHMENTS[1]);

        texture = Manager<Texture2D>::Add("Diffuse colors", GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
        m_GBuffer.AttachTexture(texture, GBUFFER_ATTACHMENTS[2]);

        texture = Manager<Texture2D>::Add("Specular colors", GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
        m_GBuffer.AttachTexture(texture, GBUFFER_ATTACHMENTS[3]);

        glDrawBuffers(sizeof(GBUFFER_ATTACHMENTS) / sizeof(unsigned), GBUFFER_ATTACHMENTS);

        m_GBuffer.AttachRenderbuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);

        m_GBuffer.Resize(width, height);

        GIR_ASSERT(m_GBuffer.IsComplete(), "Incomplete GBuffer framebuffer");

        m_GBuffer.Unbind();
    }

    void Renderer::GBufferDraw(const Scene* scene)
    {
        auto* shader = m_shaderManager.GetShader(EShaderType::GBUFFER);

        shader->Bind();
        m_GBuffer.Bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& camera = scene->GetCamera();
        shader->SetUniform("vp", camera.GetProjectionMatrix() * camera.GetViewMatrix());

        for (const auto& entity : scene->GetEntities())
        {
            shader->SetUniform("model", entity.GetTransform());
            auto* model = entity.GetModel();

            for (int i = 0; i < static_cast<int>(model->MaterialCount()); ++i)
            {
                for (const auto& mesh : model->GetMeshes(i))
                {
                    auto* vao = mesh->GetVertexArrayObject();
                    vao->Bind();
                    glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, nullptr);
                    vao->Unbind();
                }
            }
        }

        m_GBuffer.Unbind();
        shader->Unbind();
    }

} // namespace gir