#include "ShaderManager.hpp"

namespace gir
{
    ShaderManager::ShaderManager(const std::unordered_map<EShaderType, ShaderType> &sources) :
        m_shaders(static_cast<int>(EShaderType::COUNT))
    {
        for (const auto &source : sources)
        {
            m_shaders[static_cast<int>(source.first)] = Shader(source.second);
        }
    }

} // namespace gir