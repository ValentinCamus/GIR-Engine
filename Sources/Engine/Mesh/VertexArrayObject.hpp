#pragma once

#include <glad/glad.h>

// #include "Engine/Mesh/Mesh.hpp"
#include "Engine/Component/OpenGLComponent.hpp"

namespace gir
{
    constexpr unsigned bufferCount = 4;

    class VertexArrayObject : public OpenGLComponent
    {
    public:
        explicit VertexArrayObject() : OpenGLComponent() {}

        //explicit VertexArrayObject(const Mesh& mesh);

        // VertexArrayObject(VertexArrayObject&& vao) noexcept;

        ~VertexArrayObject();

        bool operator==(const VertexArrayObject& vao) const;

        void Bind() override;

        void Unbind() override;

    private:
        // TOTRY: heap allocate and compare cpu times
        // unsigned buffers[bufferCount];
    };

} // namespace gir