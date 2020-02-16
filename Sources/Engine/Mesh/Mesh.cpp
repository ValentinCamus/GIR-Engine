#include "Mesh.hpp"

#include <utility>

namespace gir
{
    Mesh::Mesh(const std::string& name, std::vector<unsigned>&& indices, std::vector<Vertex>&& vertices) :
        Component(name),
        m_indices(std::move(indices)),
        m_vertices(std::move(vertices))
    {
        m_vao.Bind();

        unsigned ibo, vbo;

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        auto vboSizeInByte = m_vertices.size() * sizeof(Vertex);
        glBufferData(GL_ARRAY_BUFFER, vboSizeInByte, &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        auto iboSizeInByte = m_indices.size() * sizeof(unsigned);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iboSizeInByte, &m_indices[0], GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        void* positionOffset = (void*)offsetof(Vertex, position);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), positionOffset);

        // Vertex normals
        glEnableVertexAttribArray(1);
        void* normalOffset = (void*)offsetof(Vertex, normal);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), normalOffset);

        // Vertex texture coords
        glEnableVertexAttribArray(2);
        void* texCoordOffset = (void*)offsetof(Vertex, textureCoordinates);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), texCoordOffset);

        m_vao.SetIndexBufferId(ibo);
        m_vao.AddVertexBufferId(vbo);

        m_vao.Unbind();
    }
} // namespace gir
