#pragma once

#include <Core/Core.hpp>

namespace gir
{
    // TODO: Add the "bound" boolean to the interface
    class Bindable
    {
    public:
        virtual ~Bindable() = default;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual bool IsBound() const = 0;

        /// A bindable is represented with an unique identifier.
        virtual unsigned GetId() const = 0;
    };
} // namespace gir