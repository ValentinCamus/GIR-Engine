#include "VertexArrayObject.hpp"

namespace gir
{
    VertexArrayObject::VertexArrayObject() : OpenGLComponent("VAO") { glGenVertexArrays(1, &m_id); }

    VertexArrayObject::~VertexArrayObject()
    {
        if (m_isIndexed) glDeleteBuffers(1, &m_ibo);
        for (unsigned buffer : m_attributeBuffers) glDeleteBuffers(1, &buffer);

        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArrayObject::Bind()
    {
        OpenGLComponent::Bind();
        glBindVertexArray(m_id);
    }

    void VertexArrayObject::Unbind()
    {
        OpenGLComponent::Unbind();
        glBindVertexArray(0);
    }

    void VertexArrayObject::AddIndexBuffer(const std::vector<unsigned>& buffer)
    {
        if (!m_isIndexed)
        {
            glGenBuffers(1, &m_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * buffer.size(), buffer.data(), GL_STATIC_DRAW);
            m_isIndexed = true;
        }
        else
            Logger::Warn("[VAO={0}] The buffer is already indexed", m_id);
    }

    unsigned VertexArrayObject::GenerateVBO()
    {
        unsigned vbo = 0;

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        m_attributeBuffers.push_back(vbo);

        return m_attributeBuffers.size() - 1;
    }

} // namespace gir