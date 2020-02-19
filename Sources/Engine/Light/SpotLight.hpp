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

        void SetUniforms(const std::string &name, Shader *shader, int slot, bool bindTextures = true) override;

    private:
        static const Mat4f m_projection;

        float m_cosInnerAngle;
        float m_cosOuterAngle;

        const Mat4f &GetProjection() override;
    };
} // namespace gir
