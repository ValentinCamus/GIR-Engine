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
    class Scene;

    class Light : public SceneComponent
    {
    public:
        Light(const std::string &name, const Mat4f &transform, const Vec3f &color);

        virtual ~Light() = default;
        
        Framebuffer *GetShadowMap();

        virtual void DrawShadowMap(const Scene *scene, Shader *shader);

        virtual void SetUniforms(const std::string &name, Shader *shader, int);

        virtual bool HasCubemapShadowmap() const;

    protected:
        Framebuffer m_shadowmap;

        Vec3f m_color;

        Mat4f GetView() const;

        virtual const Mat4f &GetProjection() = 0;
    };
} // namespace gir
