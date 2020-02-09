#ifndef MESH_HPP
#define MESH_HPP

#include <Core/Core.hpp>
#include "Component.hpp"
#include "VertexArrayObjectManager.hpp"

namespace gir
{
    class Mesh : public Component
    {
    public:
        Mesh(const std::string &name,
             std::vector<unsigned> &&indices,
             std::vector<Vec3f> &&vertices,
             std::vector<Vec3f> &&normals,
             std::vector<Vec2f> &&textureCoordinates);

        ~Mesh();

        const std::vector<unsigned> &GetIndices() const;

        const std::vector<Vec3f> &GetVertices() const;

        const std::vector<Vec3f> &GetNormals() const;

        const std::vector<Vec2f> &GetTextureCoordinates() const;

        static VertexArrayObjectManager m_vaoManager;

    private:

        const VertexArrayObject &m_vao;

        std::vector<unsigned> m_indices;

        std::vector<Vec3f> m_vertices;

        std::vector<Vec3f> m_normals;

        std::vector<Vec2f> m_textureCoordinates;
    };

} // namespace gir

#endif