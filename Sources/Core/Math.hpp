#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace gir
{
    /// @return: -1 if the sign of x is negative and 1 otherwise.
    template<class T>
    inline int Sign(const T& value) { return value < 0 ? -1 : 1; }

    /// Calculate the power of two of @value.
    template<class T>
    inline T Pow2(T value) { return value * value; }

    /// Calculate the power of three of @value.
    template<class T>
    inline T Pow3(T value) { return value * value * value; }

    /// Clamp @value between @min and @max.
    template<class T>
    inline T Clamp(T value, T min, T max) { return std::max(std::min(value, max), min); }

    /// Check if @value is between @min and @max.
    template<class T>
    inline bool InRange(T value, T min, T max) { return (value >= min && value <= max); }

    /// Calculate the factorial of @value.
    template<class T>
    inline T Fact(T value) { return (value > 0) ? value * Fact(value - 1) : 1; }

    /// Returns Value mapped from one range into another where the Value is clamped to the Input Range.
    /// (e.g. 0.5 normalized from the range 0->1 to 0->50 would result in 25)
    template<class T>
    inline T MapRange(T value, float rangeMin, float rangeMax, float newRangeMin, float newRangeMax)
    {
        return (value - rangeMin) * (newRangeMax - newRangeMin) / (rangeMax - rangeMin + newRangeMin);
    }
}

