namespace gir {

inline Shader *ShaderManager::Program(ShaderType type) { return &m_shaders[static_cast<int>(type)]; }

} // namespace gir