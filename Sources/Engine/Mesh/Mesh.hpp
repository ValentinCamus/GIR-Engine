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
        struct Vertex
        {
            Vec3f position;
            Vec3f normal;
            Vec2f textureCoordinates;
        };

    public:
        Mesh(const std::string &name, std::vector<unsigned> &&indices, std::vector<Vertex> &&vertices);

        ~Mesh() override = default;

        inline const std::vector<unsigned> &GetIndices() const { return m_indices; }

        inline const std::vector<Vertex> &GetVertices() const { return m_vertices; }

        inline unsigned Size() const { return m_indices.size(); }

        inline VertexArrayObject &GetVAO() { return m_vao; }

        inline VertexArrayObject *GetVertexArrayObject() const { return &m_vao; }

    private:
        std::vector<unsigned> m_indices;

        std::vector<Vertex> m_vertices;

        mutable VertexArrayObject m_vao;
    };
} // namespace gir
