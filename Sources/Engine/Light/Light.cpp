#include "Light.hpp"
#include <Engine/Scene/Scene.hpp>
#include <Engine/Mesh/Model.hpp>
#include <Engine/Mesh/Mesh.hpp>

namespace gir
{
    Light::Light(const std::string &name, const Mat4f &transform, const Vec3f &color) :
        SceneComponent(name, transform),
        m_shadowmap("FBO_Shadowmap_" + name),
        m_color(color)
    {
    }

    Framebuffer *Light::GetShadowMap() { return &m_shadowmap; }

    void Light::DrawShadowMap(const Scene *scene, Shader *shader)
    {
        m_shadowmap.Bind();

        glClear(GL_DEPTH_BUFFER_BIT);

        const int slot = 0;
        SetUniforms("light", shader, slot, false);
        shader->SetUniform("albedo", slot);

        Mat4f vp(GetProjection() * GetView());
        shader->SetUniform("viewProjection", vp);

        for (const auto &entity : scene->GetEntities())
        {
            shader->SetUniform("model", entity->GetTransform());
            auto *model = entity->GetModel();

            for (int i = 0; i < static_cast<int>(model->GetMaterialCount()); ++i)
            {
                auto *material = model->GetMaterial(i);

                // We only need to bind the albedo from the material
                auto attribute = material->GetAttribute(Material::EAttribute::ALBEDO);
                if (attribute.texture)
                    attribute.texture->Bind(slot);
                else
                    shader->SetUniform("albedo", Vec3f(attribute.color));

                for (const auto &mesh : model->GetMeshes(i))
                {
                    auto *vao = mesh->GetVertexArrayObject();
                    vao->Bind();
                    glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
                    vao->Unbind();
                }

                if (attribute.texture) attribute.texture->Unbind();
            }
        }

        m_shadowmap.Unbind();
    }

    void Light::SetUniforms(const std::string &name, Shader *shader, int, bool bindTextures)
    {
        shader->SetUniform(name + ".color", m_color);
    }

    bool Light::HasCubemapShadowmap() const { return false; }

    Mat4f Light::GetView() const
    {
        Mat4f view;

        const Vec3f &translation = m_transform[3];
        const Mat3f &rotation    = m_transform;

        view       = transpose(rotation);
        view[3][0] = -dot(translation, rotation[0]);
        view[3][1] = -dot(translation, rotation[1]);
        view[3][2] = -dot(translation, rotation[2]);
        view[3][3] = 1.f;
        return view;
    }
} // namespace gir