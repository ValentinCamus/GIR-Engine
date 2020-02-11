#include "Mesh.hpp"

namespace gir
{
    Mesh::Mesh(const std::string &name, const Vertices& vertices, std::vector<unsigned> indices) :
        Component(name),
        m_indices(std::move(indices)),
        m_vertices(vertices.vertices),
        m_normals(vertices.normals),
        m_textureCoordinates(vertices.textureCoordinates),
        m_tangents(vertices.tangents),
        m_biTangents(vertices.biTangents)
    {
        m_vao.Bind();
        m_vao.AddFloatBuffer(m_vertices, 3);
        m_vao.AddFloatBuffer(m_normals, 3);
        m_vao.AddFloatBuffer(m_textureCoordinates, 2);
        m_vao.AddIndexBuffer(m_indices);
        m_vao.Unbind();
    }

} // namespace gir
