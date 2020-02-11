#include "VertexArrayObject.hpp"

namespace gir
{
    VertexArrayObject::VertexArrayObject()
        : OpenGLComponent("VAO")
    {
        glGenVertexArrays(1, &m_id);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        if (m_isIndexed) glDeleteBuffers(1, &m_ibo);
        for(unsigned vbo : m_vertexBuffers) glDeleteBuffers(1, &vbo);

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

} // namespace gir