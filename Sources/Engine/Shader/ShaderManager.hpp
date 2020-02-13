#pragma once

#include <glad/glad.h>

#include <Core/Core.hpp>
#include "Shader.hpp"

namespace gir
{
    class ShaderManager
    {
    public:
        using ShaderType = std::unordered_map<GLenum, std::string>;

    public:
        /// Default constructor.
        ShaderManager() = default;

        explicit ShaderManager(const std::unordered_map<EShaderType, ShaderType> &sources);

        inline Shader* GetShader(EShaderType type);

    private:
        std::vector<Shader> m_shaders;
};
} // namespace gir

#include "ShaderManager.inl"