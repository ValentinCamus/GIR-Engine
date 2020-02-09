#include "Component.h"

namespace gir
{
    Component::Component(const std::string& name) : m_name {name} {}

    const std::string& Component::GetName() { return m_name; }

} // namespace gir
