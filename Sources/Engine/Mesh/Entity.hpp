#pragma once

#include <Core/Core.hpp>
#include <Engine/Mesh/Model.hpp>
#include <Engine/Component/SceneComponent.hpp>

namespace gir
{
    class Entity : public SceneComponent
    {
    public:
        Entity(const std::string& name,  Model* model, const Mat4f& transform = Mat4f {1.f});

        inline const Model* GetModel() const { return m_model; }
        
    private:
        Model* m_model = nullptr;
    };
} // namespace gir
