#pragma once

#include <Engine/OpenGL/OpenGL.hpp>
#include "Engine/Component/OpenGLComponent.hpp"

namespace gir
{
    class VertexArrayObject : public OpenGLComponent
    {
    public:
        explicit VertexArrayObject();

        ~VertexArrayObject() override;

        void Bind() override;

        void Unbind() override;

        inline unsigned GetIndexBufferId() const { return m_ibo; }

        inline void SetIndexBufferId(unsigned ibo)
        {
            m_ibo = ibo;
            m_isIndexed = ibo > 0;
        }

        inline unsigned GetVertexBufferId(int index) const { return m_vertexBuffers[index]; }

        inline void SetVertexBufferId(int index, unsigned vbo) { m_vertexBuffers[index] = vbo; }

        inline void AddVertexBufferId(unsigned vbo) { m_vertexBuffers.push_back(vbo); }

        inline bool operator==(const VertexArrayObject& vao) const { return m_id == vao.m_id; }

    private:
        std::vector<unsigned> m_vertexBuffers;

        unsigned m_ibo = 0;
        bool m_isIndexed = false;
    };
} // namespace gir