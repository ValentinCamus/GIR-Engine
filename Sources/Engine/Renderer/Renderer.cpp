#include "Renderer.hpp"
#include "Engine/Scene/Scene.hpp"

namespace gir
{
    Renderer::Renderer() :
        m_shaderManager {std::unordered_map<EShaderType, std::unordered_map<GLenum, std::string>> {
            {EShaderType::DEBUG,
             {{GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.vs.glsl"},
              {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/Debug.fs.glsl"}}}}},
        m_gBuffer {"GBuffer"}
    {
        // TODO: add textures to the framebuffer and fill the shader manager initializer
    }

    void Renderer::Draw(const Scene* scene)
    {
        Shader* shader;

        static float grad = 0.01f;

        switch (m_renderMode)
        {
            case RenderMode::DEBUG:
                shader = m_shaderManager.GetShader(EShaderType::DEBUG);

                shader->Bind();

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->SetUniform("uColor", {0, grad, 1, 1});

                if (grad > 1.0)
                    grad = 0.01f;
                else
                    grad += 0.001f;

                for (const auto& entity : scene->GetEntities())
                {
                    auto* model = entity.GetModel();

                    for (unsigned i = 0; i < model->MaterialCount(); ++i)
                    {
                        for (const auto& mesh : model->GetMeshes(i))
                        {
                            mesh->GetVertexArrayObject()->Bind();
                            glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
                        }
                    }
                }

                shader->Unbind();
                break;

            case RenderMode::RSM:
                break;

            default:
                Logger::Error("Invalid render mode");
                break;
        }
    }

    void Renderer::SetRenderMode(RenderMode mode) { m_renderMode = mode; }

} // namespace gir