#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace gir
{
    /// @return: -1 if the sign of x is negative and 1 otherwise.
    template<class T>
    inline int Sign(const T& value)
    {
        return value < 0 ? -1 : 1;
    }

    /// @return: the power of two of @value.
    template<class T>
    inline T Pow2(T value)
    {
        return value * value;
    }

    /// @return: the power of three of @value.
    template<class T>
    inline T Pow3(T value)
    {
        return value * value * value;
    }

    /// @return: the clamped value of @value between @min and @max.
    template<class T>
    inline T Clamp(T value, T min, T max)
    {
        return std::max(std::min(value, max), min);
    }

    /// @return: if @value is between @min and @max.
    template<class T>
    inline bool InRange(T value, T min, T max)
    {
        return (value >= min && value <= max);
    }

    /// @return: the factorial of @value.
    template<class T>
    inline T Fact(T value)
    {
        return (value > 0) ? value * Fact(value - 1) : 1;
    }

    /// @return: the value mapped from one range into another where the value is clamped to the input range.
    /// (e.g. 0.5 normalized from the range 0->1 to 0->50 would result in 25)
    template<class T>
    inline T MapRange(T value, float rangeMin, float rangeMax, float newRangeMin, float newRangeMax)
    {
        return (value - rangeMin) * (newRangeMax - newRangeMin) / (rangeMax - rangeMin + newRangeMin);
    }

    /// @return: Create a transform matrix from the world location, rotation and the 3D scale.
    inline Mat4f MakeTransform(const Vec3f& location = Vec3f(0.0f),
                               const Vec3f& rotation = Vec3f(0.0f),
                               const Vec3f& scale    = Vec3f(1.0f))
    {
        Mat4f matrix(1.0f);

        matrix = glm::translate(matrix, location);

        matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        matrix = glm::scale(matrix, scale);

        return matrix;
    }
} // namespace gir
