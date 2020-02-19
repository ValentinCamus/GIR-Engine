#pragma once

#include "Light.hpp"

namespace gir
{
    class DirectionnalLight : public Light
    {
    public:
        DirectionnalLight(const std::string &name, const Mat4f &transform, const Vec3f &color);

        void SetUniforms(const std::string &name, Shader *shader, int slot, bool bindTextures = true) override;

    private:
        static const Mat4f m_projection;

        const Mat4f &GetProjection() override;
    };
} // namespace gir
