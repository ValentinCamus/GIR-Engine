#pragma once

#include <glad/glad.h>

// #include "Engine/Mesh/Mesh.hpp"
#include "Engine/Component/OpenGLComponent.hpp"

namespace gir
{
    class VertexArrayObject : public OpenGLComponent
    {
    public:
        explicit VertexArrayObject();

        ~VertexArrayObject() override;

        template<typename T>
        inline void AddIntBuffer(const std::vector<T>& buffer, unsigned size)
        {
            unsigned layout = GenerateVBO();
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(int) * buffer.size(), buffer.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(layout);
            glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, size * sizeof(int), 0);
        }

        template<typename T>
        inline void AddFloatBuffer(const std::vector<T>& buffer, unsigned size)
        {
            unsigned layout = GenerateVBO();
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * buffer.size(), buffer.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(layout);
            glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, size * sizeof(float), 0);
        }

        void AddIndexBuffer(const std::vector<unsigned>& buffer);

        void Bind() override;

        void Unbind() override;

        inline bool operator==(const VertexArrayObject& vao) const { return m_id == vao.m_id; }

    private:
        unsigned GenerateVBO();

    private:
        std::vector<unsigned> m_attributeBuffers;

        unsigned m_ibo = 0;
        bool m_isIndexed = false;
    };

} // namespace gir