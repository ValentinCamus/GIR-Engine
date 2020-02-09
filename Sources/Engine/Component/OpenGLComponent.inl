#pragma once

#include <Core/Core.hpp>

namespace gir
{
    inline void OpenGLComponent::Bind() { m_isBound = true; };

    inline void OpenGLComponent::Unbind() { m_isBound = false; };

    inline bool OpenGLComponent::IsBound() const { return m_isBound; };

    inline unsigned OpenGLComponent::GetId() const { return m_id; };

    inline void OpenGLComponent::SetId(unsigned id) { m_id = id; }

} // namespace gir