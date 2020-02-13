#include "Mesh.hpp"

#include <utility>

namespace gir
{
    Mesh::Mesh(const std::string &name, std::vector<Vertex> vertices, std::vector<unsigned> indices)
        : Component(name)
        , m_indices(std::move(indices))
        , m_vertices(std::move(vertices))
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
        void* positionOffset = (void*) offsetof(Vertex, position);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), positionOffset);

        // Vertex normals
        glEnableVertexAttribArray(1);
        void* normalOffset = (void*) offsetof(Vertex, normal);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), normalOffset);

        // Vertex texture coords
        glEnableVertexAttribArray(2);
        void* texCoordOffset =  (void*) offsetof(Vertex, textureCoordinate);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), texCoordOffset);

        // Vertex tangent
        glEnableVertexAttribArray(3);
        void* tangentOffset =  (void*) offsetof(Vertex, tangent);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), tangentOffset);

        // Vertex bitangent
        glEnableVertexAttribArray(4);
        void* biTangentOffset =  (void*) offsetof(Vertex, bitangent);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), biTangentOffset);

        m_vao.SetIndexBufferId(ibo);
        m_vao.AddVertexBufferId(vbo);

        m_vao.Unbind();
    }

} // namespace gir
