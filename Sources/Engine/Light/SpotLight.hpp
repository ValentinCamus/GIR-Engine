#pragma once

#include "Light.hpp"

namespace gir
{
    class SpotLight : public Light
    {
    public:
        SpotLight(const std::string &name,
                  const Mat4f &transform,
                  const Vec3f &color,
                  float innerAngle,
                  float outerAngle);

        void SetUniforms(const std::string &name, Shader *shader) override;

        const Mat4f &GetProjection() const override;

    private: 
        static const Mat4f m_projection;

        float m_innerAngle;
        float m_outerAngle;
    };
} // namespace gir
