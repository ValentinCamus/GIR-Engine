#include "Shader.hpp"

namespace gir
{
    Shader::Shader(const std::unordered_map<GLenum, std::string> &sources) : OpenGLComponent("Shader")
    {
        std::vector<GLuint> stages;

        m_id = glCreateProgram();

        stages.reserve(sources.size());
        for (const auto &src : sources)
        {
            GLuint id = ParseGLSL(src.first, src.second);
            stages.push_back(id);
            glAttachShader(m_id, id);
        }

        glLinkProgram(m_id);

        for (const auto id : stages) { glDeleteShader(id); }

        GLint success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLint length;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
            auto log = std::string(length, ' ');
            glGetProgramInfoLog(m_id, length, nullptr, &log[0]);
            Logger::Error("Shader program linking failed with the following: {}", log);
        }
    }

    void Shader::operator=(Shader &&shader) noexcept
    {
        m_name      = shader.m_name;
        m_id        = shader.m_id;
        m_isBound   = shader.m_isBound;
        shader.m_id = 0;
    }

    Shader::~Shader() { 
        glDeleteProgram(m_id); }

    void Shader::Bind()
    {
        GIR_ASSERT(m_id > 0, "Invalid program ID");

        OpenGLComponent::Bind();
        glUseProgram(m_id);
    }

    void Shader::Unbind()
    {
        OpenGLComponent::Unbind();
        glUseProgram(0);
    }

    unsigned Shader::ParseGLSL(GLenum shaderType, const std::string &filename)
    {
        std::ifstream file {filename};
        GLuint id = glCreateShader(shaderType);

        if (file.is_open())
        {
            std::stringstream stream;
            stream << file.rdbuf();
            std::string src {stream.str()};

            ParseIncludes(src);

            const char *cSource = src.c_str();
            glShaderSource(id, 1, &cSource, nullptr);
            glCompileShader(id);

            GLint success;
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                GLint length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                std::string log(length, ' ');
                glGetShaderInfoLog(id, length, nullptr, &log[0]);
                Logger::Error("Shader compilation failed with the following: {}", log);
            }
        }
        else
        {
            Logger::Error("Could not open file ", filename);
        }

        return id;
    }

    void Shader::ParseIncludes(std::string &src) const
    {
        const std::regex pattern {"#include( )*\"(([A-Z]|[a-z]|[0-9]|_)*\\.glsl)\""};
        std::smatch match;

        auto begin = src.cbegin();
        while (regex_search(begin, src.cend(), match, pattern))
        {
            std::ifstream file {PROJECT_SOURCE_DIR + std::string("/Shaders/") + match[2].str()};

            std::stringstream stream;
            stream << file.rdbuf();

            src.replace(match.position(), match.length(), stream.str());
            begin = src.cbegin() + match.position() + stream.str().length();
        }
    }

    int Shader::GetUniformLocation(const std::string &name)
    {
        GLint location = -1;
        auto iterator  = m_uniforms.find(name);

        if (iterator != m_uniforms.end()) { location = iterator->second; }
        else
        {
            location = glGetUniformLocation(m_id, name.c_str());

            if (location != -1)
                m_uniforms.emplace(name, location);
            else
                Logger::Error("[Program ID={0}] Invalid uniform name: {1}", m_id, name);
        }

        return location;
    }

} // namespace gir