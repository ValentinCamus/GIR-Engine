namespace gir
{
    inline void Shader::SetUniform(const std::string &name, int value)
    {
        int location = GetUniformLocation(name);
        glUniform1i(location, value);
    }

    inline void Shader::SetUniform(const std::string &name, unsigned value)
    {
        int location = GetUniformLocation(name);
        glUniform1ui(location, value);
    }

    inline void Shader::SetUniform(const std::string &name, float value)
    {
        int location = GetUniformLocation(name);
        glUniform1f(location, value);
    }

    inline void Shader::SetUniform(const std::string &name, bool value)
    {
        int location = GetUniformLocation(name);
        glUniform1i(location, value);
    }

    inline void Shader::SetUniform(const std::string &name, const Vec3f &value)
    {
        int location = GetUniformLocation(name);
        glUniform3fv(location, 1, value_ptr(value));
    }

    inline void Shader::SetUniform(const std::string &name, const Vec4f &value)
    {
        int location = GetUniformLocation(name);
        glUniform4fv(location, 1, value_ptr(value));
    }

    inline void Shader::SetUniform(const std::string &name, const Mat4f &value)
    {
        int location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
    }

} // namespace gir