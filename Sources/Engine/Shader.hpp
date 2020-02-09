#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad.h"
#include "Bindable.hpp"
#include <Core/Types.hpp>
#include <Core/Core.hpp>

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

    using ProgramSources = std::vector<std::pair<GLenum, std::string>>;

    class Shader : public Bindable
    {
    public:
        Shader()               = delete;
        Shader(const Shader &) = delete;
        void operator=(const Shader &) = delete;

        Shader(const ProgramSources &sources);

        Shader(Shader &&shader) noexcept;

        ~Shader();

        void Bind() override;

        void Unbind() override;

        bool IsBound() override;

        unsigned GetId() override;

        inline void SetUniform(const std::string &name, int value);

        inline void SetUniform(const std::string &name, unsigned value);

        inline void SetUniform(const std::string &name, float value);

        inline void SetUniform(const std::string &name, bool value);

        inline void SetUniform(const std::string &name, const Vec3 &value);

        // inline void SetUniform(const std::string &name, const Vec4 &value);

        inline void SetUniform(const std::string &name, const Mat4 &value);

        static const char *prefix;

    private:
        unsigned ParseGLSL(GLenum shaderType, const std::string &filename, std::vector<std::string> &uniforms);
        void ParseIncludes(std::string &src) const;

        unsigned m_programID;

        std::unordered_map<std::string, GLint> m_uniforms;

        bool m_bound = false;
    };

} // namespace gir

#include "Shader.inl"

#endif