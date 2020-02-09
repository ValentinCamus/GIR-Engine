#include "Mesh.hpp"

namespace gir
{
    Mesh::Mesh(const std::string &name,
               Material *material,
               std::vector<unsigned> &&indices,
               std::vector<Vec3f> &&vertices,
               std::vector<Vec3f> &&normals,
               std::vector<Vec2f> &&textureCoordinates) :
        Component {name},
        m_material {material},
        m_vertices {std::move(vertices)},
        m_normal {std::move(normals)},
        m_textureCoordinates {std::move(textureCoordinates)}
    {
        m_vaoManager.AddVertexArrayObject(*this);
    }

    Mesh::~Mesh() { VertexArrayObjectManager::DeleteVertexArrayObject(m_vao); }

    const Material *Mesh::GetMaterial() const { return m_material; }

    const std::vector<unsigned> &Mesh::GetIndices() const { return m_indices; }

    const std::vector<Vec3f> &Mesh::GetVertices() const { return m_vertices; }

    const std::vector<Vec3f> &Mesh::GetNormals() const { return m_normals; }

    const std::vector<Vec2f> &Mesh::GetTextureCoordinates() const { return m_textureCoordinates; }

} // namespace gir
