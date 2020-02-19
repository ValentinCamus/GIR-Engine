#include "PointLight.hpp"
#include <Engine/Scene/Scene.hpp>
#include <Engine/Mesh/Model.hpp>
#include <Engine/Mesh/Mesh.hpp>

namespace gir
{
    const Mat4f PointLight::m_projection = glm::perspective(PI / 2, 1.f, NEAR_Z, FAR_Z);

    PointLight::PointLight(const std::string& name, const Mat4f& transform, const Vec3f& color) :
        Light(name, transform, color)
    {
        m_shadowmap.Bind();
        m_shadowmap.AttachTexture(
            std::make_unique<Texture>(
                name + "_shadowmap", GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_TEXTURE_CUBE_MAP),
            GL_DEPTH_ATTACHMENT);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        auto* texture = m_shadowmap.GetTexture(0);

        texture->Bind();
        texture->SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        texture->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        texture->SetParameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        texture->Unbind();

        m_shadowmap.Resize(1200, 1200);

        GIR_ASSERT(m_shadowmap.IsComplete(), "Incomplete pointlight framebuffer");

        m_shadowmap.Unbind();
    }

    void PointLight::DrawShadowMap(const Scene* scene, Shader* shader)
    {
        m_shadowmap.Bind();
        glClear(GL_DEPTH_BUFFER_BIT);

        Vec3f position(m_transform[3]);

        Mat4f vp[6] = {m_projection * glm::lookAt(position, position + Vec3f(1.f, 0.f, 0.f), Vec3f(0.f, -1.f, 0.f)),
                       m_projection * glm::lookAt(position, position + Vec3f(-1.f, 0.f, 0.f), Vec3f(0.f, -1.f, 0.f)),
                       m_projection * glm::lookAt(position, position + Vec3f(0.f, 1.f, 0.f), Vec3f(0.f, 0.f, 1.f)),
                       m_projection * glm::lookAt(position, position + Vec3f(0.f, -1.f, 0.f), Vec3f(0.f, 0.f, -1.f)),
                       m_projection * glm::lookAt(position, position + Vec3f(0.f, 0.f, 1.f), Vec3f(0.f, -1.f, 0.f)),
                       m_projection * glm::lookAt(position, position + Vec3f(0.f, 0.f, -1.f), Vec3f(0.f, -1.f, 0.f))};

        shader->SetUniform("lightPosition", position);

        for (int i = 0; i < 6; ++i) shader->SetUniform("vp[" + std::to_string(i) + "]", vp[i]);

        for (const auto& entity : scene->GetEntities())
        {
            shader->SetUniform("model", entity->GetTransform());
            auto* model = entity->GetModel();

            for (int i = 0; i < static_cast<int>(model->GetMaterialCount()); ++i)
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

        m_shadowmap.Unbind();
    }

    void PointLight::SetUniforms(const std::string& name, Shader* shader, int slot, bool bindTextures)
    {
        Light::SetUniforms(name, shader, slot, bindTextures);
        shader->SetUniform(name + ".type", static_cast<unsigned>(0));
        shader->SetUniform(name + ".position", Vec3f(m_transform[3]));

        shader->SetUniform(name + ".shadowmapPL", slot);
    }

    bool PointLight::HasCubemapShadowmap() const { return true; }

    const Mat4f& PointLight::GetProjection() { return m_projection; }
} // namespace gir