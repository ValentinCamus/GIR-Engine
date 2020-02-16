#pragma once

#include <Core/Core.hpp>
#include <Core/Math.hpp>
#include <Engine/Component/SceneComponent.hpp>
#include <Engine/Shader/Shader.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

#define NEAR_Z 0.2f
#define FAR_Z 100.f

namespace gir
{
    class Light : public SceneComponent
    {
    public:
        Light(const std::string &name, const Mat4f &transform, const Vec3f &color);

        ~Light() override = default;

        // TODO
        // void DrawShadowMap(const Scene& scene);

        Mat4f GetView() const;

        // TODO
        // const Framebuffer *GetShadowMap() const;

        virtual void SetUniforms(const std::string &name, Shader *shader);

        virtual const Mat4f &GetProjection() const = 0;

    protected:
        // Framebuffer m_shadowMap;

        Vec3f m_color;
    };
} // namespace gir
