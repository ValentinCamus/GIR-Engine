namespace gir
{
    inline Shader* ShaderManager::GetShader(EShaderType type)
    {
        return &m_shaders[static_cast<int>(type)];
    }

} // namespace gir