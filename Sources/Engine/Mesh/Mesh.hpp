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
        struct Vertices
        {
            std::vector<Vec3f> vertices;
            std::vector<Vec3f> normals;
            std::vector<Vec2f> textureCoordinates;
            std::vector<Vec3f> tangents = {};
            std::vector<Vec3f> biTangents = {};
        };

    public:
        Mesh(const std::string &name, const Vertices& vertices, std::vector<unsigned> indices);

        ~Mesh() override = default;

        inline const std::vector<unsigned> &GetIndices() const { return m_indices; }

        inline const std::vector<Vec3f> &GetVertices() const { return m_vertices; }

        inline const std::vector<Vec3f> &GetNormals() const { return m_normals; }

        inline const std::vector<Vec2f> &GetTextureCoordinates() const { return m_textureCoordinates; }

        inline const std::vector<Vec3f> &GetTangent() const { return m_tangents; }

        inline const std::vector<Vec3f> &GetBiTangent() const { return m_biTangents; }

    private:
        std::vector<unsigned> m_indices;

        std::vector<Vec3f> m_vertices;

        std::vector<Vec3f> m_normals;

        std::vector<Vec2f> m_textureCoordinates;

        std::vector<Vec3f> m_tangents;

        std::vector<Vec3f> m_biTangents;

        VertexArrayObject m_vao;
    };

} // namespace gir
