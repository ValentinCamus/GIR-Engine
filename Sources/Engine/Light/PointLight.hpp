#pragma once

#include "Light.hpp"

namespace gir
{
    class PointLight : public Light
    {
    public:
        PointLight(const std::string& name, const Mat4f& transform, const Vec3f& color);

        void DrawShadowMap(const Scene* scene, Shader* shader) override;

        void SetUniforms(const std::string& name, Shader* shader, int slot, bool bindTextures) override;

        bool HasCubemapShadowmap() const override;

    private:
        static const Mat4f m_projection;

        const Mat4f& GetProjection() override;
    };
} // namespace gir