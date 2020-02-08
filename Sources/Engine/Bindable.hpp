#pragma once

#include <Core/Core.hpp>

namespace gir
{
    class Bindable
    {
    public:
        virtual ~Bindable() = default;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual bool IsBound() const = 0;

        /// A bindable is represented with an unique identifier.
        virtual unsigned GetId() const = 0;

        virtual const char* GetName() const = 0;
    };
} // namespace gir