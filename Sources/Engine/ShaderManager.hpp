#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

// TODO: Handle the collision with the include in the application
#include <glad/glad.h>
#include <string>
#include <vector>
#include <utility>
#include "Shader.hpp"

namespace gir
{
    class ShaderManager
    {
    public:
        ShaderManager() = default;

        ShaderManager(const std::vector<std::pair<EShaderType, ProgramSources>> &sources);

        inline Shader *Program(EShaderType type);

    private:
        std::vector<Shader> m_shaders;
    };

} // namespace gir

#include "ShaderManager.inl"

#endif