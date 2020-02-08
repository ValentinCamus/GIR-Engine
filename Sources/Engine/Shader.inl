namespace gir {

inline void Shader::SetUniform(const std::string &name, int value) { glUniform1i(m_uniforms[name], value); }

inline void Shader::SetUniform(const std::string &name, unsigned value) { glUniform1ui(m_uniforms[name], value); }

inline void Shader::SetUniform(const std::string &name, float value) { glUniform1f(m_uniforms[name], value); }

inline void Shader::SetUniform(const std::string &name, bool value) { glUniform1i(m_uniforms[name], value ? 1 : 0); }

inline void Shader::SetUniform(const std::string &name, const Vec3 &value) {
    glUniform3fv(m_uniforms[name], 1, value_ptr(value));
}

// inline void Shader::SetUniform(const std::string &name, const Vec4 &value) { glUniform4fv(m_uniforms[name], 1,
// value_ptr(value)); }

inline void Shader::SetUniform(const std::string &name, const Mat4 &value) {
    glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, value_ptr(value));
}

} // namespace gir