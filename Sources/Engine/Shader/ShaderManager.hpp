#pragma once

#include <glad/glad.h>

#include <Core/Core.hpp>
#include "Shader.hpp"

namespace gir
{
    class ShaderManager
    {
    public:
        ShaderManager() = default;

        ShaderManager(const std::unordered_map<EShaderType, std::unordered_map<GLenum, std::string>> &sources);

        inline Shader* GetShader(EShaderType type);

    private:
        std::vector<Shader> m_shaders;
    };

} // namespace gir

#include "ShaderManager.inl"