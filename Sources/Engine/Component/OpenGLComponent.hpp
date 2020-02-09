#pragma once

#include <Core/Core.hpp>

namespace gir
{
    class OpenGLComponent
    {
    public:
        virtual ~OpenGLComponent() = default;

        virtual inline void Bind();

        virtual inline void Unbind();

        virtual inline bool IsBound() const;

        virtual inline unsigned GetId() const;

        virtual inline void SetId(unsigned id);

    protected:
        /// A bindable is represented with an unique identifier.
        unsigned m_id = 0;

        bool m_isBound = false;
    };
} // namespace gir

#include "OpenGLComponent.inl"