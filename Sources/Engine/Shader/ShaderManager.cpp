#include "ShaderManager.hpp"

namespace gir
{
    ShaderManager::ShaderManager(const std::unordered_map<EShaderType,
                                                          std::unordered_map<GLenum, std::string>> &sources) :
        m_shaders(static_cast<int>(EShaderType::COUNT))
    {
        for (const auto &source : sources)
        {
            m_shaders[static_cast<int>(source.first)] = std::move(Shader(source.second));
        }
    }

} // namespace gir