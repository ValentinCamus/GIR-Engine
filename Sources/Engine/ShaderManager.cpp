#include "ShaderManager.hpp"

namespace gir
{
    ShaderManager::ShaderManager(const std::vector<std::pair<EShaderType, ProgramSources>> &sources) :
        m_shader(static_cast<int>(EShaderType::COUNT))
    {
        for (const auto &shader : sources) { m_shaders[static_cast<int>(shader.first)] = Shader {shader.second}; }
    }

} // namespace gir