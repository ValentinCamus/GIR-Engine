#pragma once

#include <glad/glad.h>

#include <Core/Core.hpp>

#include "Engine/Component/OpenGLComponent.hpp"

namespace gir
{
    enum class EShaderType
    {
        GBUFFER           = 0,
        DEFERRED_LIGHTING = 1,
        SHADOW_MAPPING    = 2,
        DEBUG             = 3,
        COUNT             = 4
    };

    class Shader : public OpenGLComponent
    {
    public:
        explicit Shader() : OpenGLComponent() {}

        Shader(const std::unordered_map<GLenum, std::string> &sources);

        ~Shader() override;

        void Bind() override;

        void Unbind() override;

        inline void SetUniform(const std::string &name, int value);

        inline void SetUniform(const std::string &name, unsigned value);

        inline void SetUniform(const std::string &name, float value);

        inline void SetUniform(const std::string &name, bool value);

        inline void SetUniform(const std::string &name, const Vec3f &value);

        inline void SetUniform(const std::string &name, const Vec4f &value);

        inline void SetUniform(const std::string &name, const Mat4f &value);

        static const char *prefix;

    private:
        unsigned ParseGLSL(GLenum shaderType, const std::string &filename, std::vector<std::string> &uniforms);

        void ParseIncludes(std::string &src) const;

        int GetUniformLocation(const std::string& name);

    private:
        std::unordered_map<std::string, GLint> m_uniforms;
    };

} // namespace gir

#include "Shader.inl"