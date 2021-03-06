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

        void SetUniforms(const std::string &name, Shader *shader, int slot, bool bindTextures) override;

        inline float GetInnerAngle() const { return m_innerAngle; }
        inline float GetOuterAngle() const { return m_outerAngle; }

        inline void SetInnerAngle(float innerAngle)
        {
            m_innerAngle = innerAngle;
            m_cosInnerAngle = cos(innerAngle);
        }

        inline void SetOuterAngle(float outerAngle)
        {
            m_outerAngle = outerAngle;
            m_cosOuterAngle = cos(outerAngle);
        }

    private:
        static const Mat4f m_projection;

        float m_innerAngle;
        float m_outerAngle;

        float m_cosInnerAngle;
        float m_cosOuterAngle;

        const Mat4f &GetProjection() override;
    };
} // namespace gir
