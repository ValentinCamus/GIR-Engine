#ifndef VERTEXARRAYOBJECTMANAGER_HPP
#define VERTEXARRAYOBJECTMANAGER_HPP

#include <Core/Core.hpp>
#include "VertexArrayObject.hpp"
#include "Material.hpp"

namespace gir
{
    // If performance is an issue:
    //      --> TODO: VAO packing + everything it implies (bindless textures ? UBOs ?)
    class VertexArrayObjectManager
    {
    public:
        static void AddVertexArrayObject(const Mesh& mesh);

        static void DeleteVertexArrayObject(const VertexArrayObject& vao);

        static inline void BindVAO(int i);

        static inline unsigned VAOCount();

    private:
        static std::vector<std::pair<Material*, VertexArrayObject>> m_vaosByMaterial;

        VertexArrayObjectManager() = default;
    };

} // namespace gir

#include "VertexArrayObjectManager.inl"

#endif