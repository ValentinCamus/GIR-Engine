
#include "Renderer.hpp"
#include "Engine/Scene/Scene.hpp"
#include "Engine/Manager/Manager.hpp"
#include "Engine/Light/Light.hpp"

namespace gir
{
    Renderer::Renderer(unsigned width, unsigned height) :
        m_shaderManager(GetDefaultShaderManager()),
        m_GBuffer("GBuffer")
    {
        SetRenderMode(ERenderMode::DIRECT);

        m_quad = std::make_unique<Quad>("DeferredShadingQuad");

        InitializeGBuffer(width, height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Renderer::Draw(Framebuffer* framebuffer, const Scene* scene)
    {
        GBufferPrepass(scene, framebuffer);

        switch (m_renderMode)
        {
            case ERenderMode::UNLIT:
                AlbedoDebugPass(scene, framebuffer);
                break;

            case ERenderMode::DIRECT:
                DeferredLightingPass(scene, false, framebuffer);
                break;

            case ERenderMode::RSM:
                DeferredLightingPass(scene, true, framebuffer);
                break;

            default:
                Logger::Error("Invalid render mode");
                break;
        }
    }

    ShaderManager Renderer::GetDefaultShaderManager()
    {
        return ShaderManager({
            {
                EShaderType::GBUFFER,
                {
                    {GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.vs.glsl"},
                    {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/GBuffer.fs.glsl"}
                }
            },
            {
                EShaderType::DEFERRED_LIGHTING,
                {
                    {GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/CookTorrance.vs.glsl"},
                    {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/CookTorrance.fs.glsl"}
                }
            },
            {
                EShaderType::DEBUG,
                {
                    {GL_VERTEX_SHADER, PROJECT_SOURCE_DIR "/Shaders/Unlit.vs.glsl"},
                    {GL_FRAGMENT_SHADER, PROJECT_SOURCE_DIR "/Shaders/Unlit.fs.glsl"}
                }
            }
        });
    }

    void Renderer::InitializeGBuffer(unsigned width, unsigned height)
    {
        m_GBuffer.Bind();

        std::vector<GLuint> attachments {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};

        m_GBuffer.AttachTexture(std::make_unique<Texture>("position", GL_RGB32F, GL_RGB, GL_FLOAT), attachments[0]);
        m_GBuffer.AttachTexture(std::make_unique<Texture>("normalMetalness", GL_RGBA32F, GL_RGBA, GL_FLOAT), attachments[1]);
        m_GBuffer.AttachTexture(std::make_unique<Texture>("albedoRoughness", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE), attachments[2]);

        glDrawBuffers(attachments.size(), attachments.data());

        m_GBuffer.AttachRenderbuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);

        m_GBuffer.Resize(width, height);

        GIR_ASSERT(m_GBuffer.IsComplete(), "Incomplete GBuffer framebuffer");

        m_GBuffer.Unbind();

        glEnable(GL_FRAMEBUFFER_SRGB);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glPolygonOffset(.85f, .75f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    }

    void Renderer::SetRenderMode(ERenderMode mode)
    {
        m_renderMode = mode;

        auto shader = m_shaderManager.GetShader(EShaderType::DEFERRED_LIGHTING);
        shader->SetUniform("useIndirectLighting", mode == ERenderMode::RSM || mode == ERenderMode::RSMGS);
    }

    void Renderer::GBufferPrepass(const Scene* scene, Framebuffer* framebuffer)
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
        m_GBuffer.BlitDepthBuffer(framebuffer);
        m_GBuffer.Unbind();

        shader->Unbind();
    }

    void Renderer::AlbedoDebugPass(const Scene* scene, Framebuffer* framebuffer)
    {
        auto* shader = m_shaderManager.GetShader(EShaderType::DEBUG);

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
    }

    void Renderer::DeferredLightingPass(const Scene* scene, bool useIndirectLighting, Framebuffer* framebuffer)
    {
        /// Shadow map pass
        const auto& lights = scene->GetLights();

        DrawShadowMaps(scene, framebuffer);

        auto shader = m_shaderManager.GetShader(EShaderType::DEFERRED_LIGHTING);
        shader->Bind();

        framebuffer->Bind();
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        const auto& camera = scene->GetCamera();
        shader->SetUniform("cameraPosition", Vec3f(camera.GetTransform()[3]));

        shader->SetUniform("lightCount", static_cast<unsigned>(lights.size()));

        // Binding the light's uniforms and the shadowmap texture
        for (int i = 0; i < static_cast<int>(lights.size()); ++i)
        {
            const int index = Light::rsmTextureCount * i + 1;
            lights[i]->SetUniforms("lights[" + std::to_string(i) + "]", shader, index);
            for (int j = 0; j < Light::rsmTextureCount; ++j)
            {
                lights[i]->GetShadowMap()->GetTexture(j)->Bind(index + j);
            }
        }

        // Binding the GBuffer textures
        for (int i = 0; i < static_cast<int>(m_GBuffer.GetTextureCount()); ++i)
        {
            auto* texture   = m_GBuffer.GetTexture(i);
            const int index = i + Light::rsmTextureCount * static_cast<int>(lights.size()) + 1;
            texture->Bind(index);
            shader->SetUniform(texture->GetName(), index);
        }

        auto* vao = m_quad->GetVertexArrayObject();
        vao->Bind();

        // Draw the quad
        glDrawElements(GL_TRIANGLES, m_quad->GetIndices().size(), GL_UNSIGNED_INT, nullptr);

        vao->Unbind();

        // Unbind everything
        for (int i = 0; i < static_cast<int>(m_GBuffer.GetTextureCount()); ++i)
        {
            m_GBuffer.GetTexture(i)->Unbind();
        }

        for (const auto & light : lights)
        {
            for (int j = 0; j < Light::rsmTextureCount; ++j)
            {
                light->GetShadowMap()->GetTexture(j)->Unbind();
            }
        }

        framebuffer->Unbind();
        shader->Unbind();

        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::DrawShadowMaps(const Scene* scene, Framebuffer* framebuffer)
    {
        const auto& lights = scene->GetLights();

        // Quick and dirty, but faster than potentially switching programs every iteration
        auto* shader = m_shaderManager.GetShader(EShaderType::SHADOW_MAPPING);
        shader->Bind();
        for (const auto & light : lights)
        {
            if (!light->HasCubemapShadowmap()) light->DrawShadowMap(scene, shader);
        }
        shader->Unbind();

        shader = m_shaderManager.GetShader(EShaderType::SHADOW_MAPPING_PL);
        shader->Bind();

        for (const auto & light : lights)
        {
            if (light->HasCubemapShadowmap()) light->DrawShadowMap(scene, shader);
        }
        shader->Unbind();
    }

} // namespace gir