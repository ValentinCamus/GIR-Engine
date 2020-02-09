#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

namespace gir
{
    class Component
    {
    public:
        Component(const std::string& name);

        ~Component() = default;

        const std::string& GetName();

    private:
        std::string name;
    };

} // namespace gir

#endif