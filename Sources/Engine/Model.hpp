#ifndef MODEL_HPP
#define MODEL_HPP

#include <Core/Core.hpp>
#include "Component.hpp"
#include "Mesh.hpp"

namespace gir
{
    class Model : public Component
    {
    public:


    private:
        std::vector<Mesh> m_meshes;
    };
} // namespace gir

#endif