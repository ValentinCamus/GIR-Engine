#ifndef TYPES_HPP
#define TYPES_HPP

#include <glm/glm.hpp>


namespace gir
{
    using Vec2f = glm::vec2;
    using Vec3f = glm::vec3;
    using Vec4f = glm::vec4;

    using Vec2i = glm::ivec2;
    using Vec3i = glm::ivec3;
    using Vec4i = glm::ivec4;

    using Mat2x3f = glm::mat2x3;
    using Mat2x4f = glm::mat2x4;
    using Mat2x2f = glm::mat2x2;
    using Mat2f = glm::mat2;

    using Mat3x2f = glm::mat3x2;
    using Mat3x3f = glm::mat3x3;
    using Mat3x4f = glm::mat3x4;
    using Mat3f = glm::mat3;

    using Mat4x2f = glm::mat4x2;
    using Mat4x3f = glm::mat4x3;
    using Mat4x4f = glm::mat4x4;
    using Mat4f = glm::mat4;
}

#endif