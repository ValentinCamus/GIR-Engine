#ifndef MESH_HPP
#define MESH_HPP

#include <Core/Core.hpp>
#include "Component.hpp"
#include "Material.hpp"
#include "VertexArrayObjectManager.hpp"

namespace gir
{
    class Mesh : public Component
    {
    public:
        Mesh(const std::string &name,
             Material *material,
             std::vector<unsigned> &&indices,
             std::vector<Vec3f> &&vertices,
             std::vector<Vec3f> &&normals,
             std::vector<Vec2f> &&textureCoordinates);

        ~Mesh();

        const Material *GetMaterial() const;

        const std::vector<unsigned> &GetIndices() const;

        const std::vector<Vec3f> &GetVertices() const;

        const std::vector<Vec3f> &GetNormals() const;

        const std::vector<Vec2f> &GetTextureCoordinates() const;

    private:
        Material *m_material;

        std::vector<unsigned> m_indices;

        std::vector<Vec3f> m_vertices;

        std::vector<Vec3f> m_normals;

        std::vector<Vec2f> m_textureCoordinates;
    };

} // namespace gir

#endif