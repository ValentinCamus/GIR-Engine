#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    class Material : public Component
    {
    public:
        inline bool operator==(const Material& material) const { return GetName() == material.GetName(); }

    private:

    };

} // namespace gir
