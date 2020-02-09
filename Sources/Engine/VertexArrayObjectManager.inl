namespace gir
{
    inline void VertexArrayObjectManager::BindVAO(int i) { m_vaos[i].Bind(); }

    inline unsigned VertexArrayObjectManager::VAOCount() { return static_cast<unsigned>(m_vaos.size()); }
} // namespace gir