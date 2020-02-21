#pragma once

#include <Core/Core.hpp>
#include <Core/Math.hpp>
#include <Engine/Component/SceneComponent.hpp>
#include <Engine/Shader/Shader.hpp>
#include <Engine/Framebuffer/Framebuffer.hpp>

#define NEAR_Z 0.4f
#define FAR_Z 45.f

namespace gir
{
    class Scene;

    class Light : public SceneComponent
    {
    public:
        Light(const std::string &name, const Mat4f &transform, const Vec3f &color);

        ~Light() override = default;

        Framebuffer *GetShadowMap();

        virtual void DrawShadowMap(const Scene *scene, Shader *shader);

        virtual void SetUniforms(const std::string &name, Shader *shader, int, bool);

        virtual bool HasCubemapShadowmap() const;

        inline const Vec3f& GetColor() const { return m_color; }

        inline void SetColor(const Vec3f& color) { m_color = color; }

        constexpr static int RSM_TEXTURES_COUNT = 4;

    protected:
        Framebuffer m_shadowmap;

        Vec3f m_color;

        Mat4f GetView() const;

        virtual const Mat4f &GetProjection() = 0;
    };
} // namespace gir
