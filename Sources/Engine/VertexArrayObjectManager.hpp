#ifndef VERTEXARRAYOBJECTMANAGER_HPP
#define VERTEXARRAYOBJECTMANAGER_HPP

#include <Core/Core.hpp>
#include "VertexArrayObject.hpp"

namespace gir
{
    // If performance is an issue:
    //      --> TODO: VAO packing + everything it implies (bindless textures ? UBOs ?)
    class VertexArrayObjectManager
    {
    public:
        VertexArrayObjectManager() = default;

        ~VertexArrayObjectManager() = default;

        void AddVertexArrayObject(const Mesh& mesh);

        void DeleteVertexArrayObject(const VertexArrayObject& vao);

        inline void BindVAO(int i);

        inline unsigned VAOCount();

    private:
        std::vector<VertexArrayObject> m_vaos;
    };

} // namespace gir

#include "VertexArrayObjectManager.inl"

#endif