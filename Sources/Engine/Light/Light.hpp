#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/SceneComponent.hpp>

namespace gir
{
    class Light : public SceneComponent
    {
    public:
        Light(const std::string& name);

        virtual ~Light();

    private:

    };

} // namespace gir
