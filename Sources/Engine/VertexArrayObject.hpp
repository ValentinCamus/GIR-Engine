#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP

#include <glad/glad.h>
#include "Bindable.hpp"
#include "Mesh.hpp"

namespace gir
{
    class VertexArrayObject : public Bindable
    {
    public:
        VertexArrayObject(const Mesh& mesh);

        VertexArrayObject(VertexArrayObject&& vao) noexcept;

        ~VertexArrayObject();

        bool operator==(const VertexArrayObject& vao) const;

        void Bind() override;

        void Unbind() override;

        bool IsBound() override;

        unsigned GetId() override;

        static constexpr bufferCount = 4;

    private:
        unsigned m_vaoID;

        // TOTRY: heap allocate and compare cpu times
        unsigned buffers[bufferCount];

        bool m_bound = false;
    };

} // namespace gir

#endif