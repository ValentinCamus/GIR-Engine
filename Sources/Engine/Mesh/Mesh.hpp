#pragma once

#include <Core/Core.hpp>
#include <Engine/Material/Material.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Mesh/VertexArrayObject.hpp>

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
             std::vector<Vec2f> &&textureCoordinates,
             std::vector<Vec3f> &&tangents,
             std::vector<Vec3f> &&bitangents);

        ~Mesh() = default;

        Material *GetMaterial();

        unsigned Size() const;

        const std::vector<unsigned> &GetIndices() const;

        const std::vector<Vec2f> &GetTextureCoordinates() const;

        VertexArrayObject *GetVertexArrayObject() const;

    private:
        Material *m_material;

        std::vector<unsigned> m_indices;

        std::vector<Vec3f> m_vertices;

        std::vector<Vec3f> m_normals;

        std::vector<Vec2f> m_textureCoordinates;

        std::vector<Vec3f> m_tangents;

        std::vector<Vec3f> m_bitangents;

        mutable VertexArrayObject m_vao;
    };

} // namespace gir
