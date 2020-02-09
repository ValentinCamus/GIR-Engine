#include "VertexArrayObject.hpp"

namespace gir
{
    VertexArrayObject::VertexArrayObject(const Mesh& mesh) : Bindable {}
    {
        glGenVertexArrays(1, &m_vaoID);
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

    VertexArrayObject::VertexArrayObject(VertexArrayObject&& vao) noexcept : Bindable {}
    {
        m_vaoID     = vao.m_vaoID;
        vao.m_vaoID = 0;

        m_bound = vao.m_bound;

        for (int i = 0; i < bufferCount; ++i)
        {
            m_buffers[i]     = vao.m_buffers[i];
            vao.m_buffers[i] = 0;
        }
    }

    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteBuffers(bufferCount, m_buffers);
        glDeleteVertexArrays(1, &m_vaoID);
    }

    bool VertexArrayObject::operator==(const VertexArrayObject& vao) const { return m_vaoID == vao.m_vaoID; }

    void VertexArrayObject::Bind() override
    {
        glBindVertexArray(m_vaoID);
        m_bound = true;
    }

    void VertexArrayObject::Unbind() override
    {
        glBindVertexArray(0);
        m_bound = false
    }

    bool VertexArrayObject::IsBound() override { return m_bound; }

    unsigned VertexArrayObject::GetId() override { return m_vaoID; }
} // namespace gir