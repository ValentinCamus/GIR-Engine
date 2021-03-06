#pragma once

#include <Core/Core.hpp>

namespace gir
{
    class Component
    {
    public:
        explicit Component(const std::string& name);

        virtual ~Component() = default;

        inline const std::string& GetName() const { return m_name; };

    protected:
        std::string m_name;
    };

} // namespace gir