#pragma once

#include "Light.hpp"

namespace gir
{
    class PointLight : public Light
    {
    public:
        PointLight(const std::string& name, const Mat4f& transform, const Vec3f& color);

        void SetUniforms(const std::string& name, Shader* shader) override;

        const Mat4f& GetProjection() const override;

    private:
        static const Mat4f m_projection;
    };
} // namespace gir