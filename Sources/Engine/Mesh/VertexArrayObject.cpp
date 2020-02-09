#include "VertexArrayObject.hpp"

namespace gir
{
    /*
    VertexArrayObject::VertexArrayObject(const Mesh& mesh) : Bindable {}
    {
        glGenVertexArrays(1, &m_id);
        glGenBuffers(bufferCount, m_buffers);
        glBindVertexArray(m_vaoID);

        const auto& indices = mesh.GetIndices();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indices.size(), indices.data(), GL_STATIC_DRAW);

        const auto& vertices = mesh.GetVertices();
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        const auto& normals = mesh.GetNormals();
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned) * normals.size(), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);

        const auto& textureCoordinates = mesh.GetTextureCoordinates();
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[3]);
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(unsigned) * textureCoordinates.size(), textureCoordinates.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
    */

    /*
    VertexArrayObject::VertexArrayObject(VertexArrayObject&& vao) noexcept : OpenGLComponent {}
    {
        m_id = vao.m_id;
        vao.m_id = 0;

        m_isBound = vao.m_isBound;

        for (int i = 0; i < bufferCount; ++i)
        {
            m_buffers[i]     = vao.m_buffers[i];
            vao.m_buffers[i] = 0;
        }
    }
    */

    VertexArrayObject::~VertexArrayObject()
    {
        // glDeleteBuffers(bufferCount, m_buffers);
        glDeleteVertexArrays(1, &m_id);
    }

    bool VertexArrayObject::operator==(const VertexArrayObject& vao) const { return m_id == vao.m_id; }

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