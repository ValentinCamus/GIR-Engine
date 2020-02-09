#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneComponent.hpp"
#include "Model.hpp"

namespace gir
{
    class Entity : public SceneComponent
    {
    public:
        Entity(const std::string& name, const Mat4f& transform = Mat4f {1.f}, const Model& model);

        const Model& model() const;
        
    private:
        const Model& m_model;
    };

} // namespace gir

#endif