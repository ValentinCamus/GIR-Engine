#include "Material.hpp"

namespace gir
{
    bool operator==(const Material& material) const { return m_name == material.name; }
} // namespace gir