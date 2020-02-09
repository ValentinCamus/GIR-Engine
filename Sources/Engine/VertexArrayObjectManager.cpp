#include "VertexArrayObjectManager.hpp"

namespace gir
{
    void VertexArrayObjectManager::AddVertexArrayObject(const Mesh& mesh) { m_vaos.emplace_back(mesh); }

    void VertexArrayObjectManager::DeleteVertexArrayObject(const VertexArrayObject& vao)
    {
        GIR_ASSERT(m_vaos.find(vao) != m_vaos.cend());

        m_vaos.erase(m_vaos.find(vao));
    }
} // namespace gir