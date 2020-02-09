#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Component.hpp"

namespace gir
{
    class Material : public Component
    {
    public:
        bool operator==(const Material& material) const;
    private:
    };
} // namespace gir

#endif