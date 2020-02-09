#include "Mesh.hpp"

namespace gir
{
    VertexArrayObjectManager Mesh::m_vaoManager {};

    Mesh::Mesh(const std::string &name,
               std::vector<unsigned> &&indices,
               std::vector<Vec3f> &&vertices,
               std::vector<Vec3f> &&normals,
               std::vector<Vec2f> &&textureCoordinates) :
        Component {name},
        m_vertices {std::move(vertices)},
        m_normal {std::move(normals)},
        m_textureCoordinates {std::move(textureCoordinates)}
    {
        m_vaoManager.AddVertexArrayObject(*this);
    }

    Mesh::~Mesh() { m_vaoManager.DeleteVertexArrayObject(m_vao); }

    const std::vector<unsigned> &Mesh::GetIndices() const { return m_indices; }

    const std::vector<Vec3f> &Mesh::GetVertices() const { return m_vertices; }

    const std::vector<Vec3f> &Mesh::GetNormals() const { return m_normals; }

    const std::vector<Vec2f> &Mesh::GetTextureCoordinates() const { return m_textureCoordinates; }

} // namespace gir
