#pragma once

#include <array>
#include <cstddef>

#include "engine/vector.h"


namespace luna
{
    /// @brief Represent a 3D face, which has three integers as fields - indices of vertices
    struct Face
    {
        int a{};
        int b{};
        int c{};

        /// @brief Creates a face. The parameters 
        /// that you have to pass in this constructor are indices of vertices
        Face(int a, int b, int c)
            : a{a}, b{b}, c{c} {}
    };
    
    /// @brief Represents a 2D triangle
    struct Triangle
    {
    private:
        std::array<luna::Vector2, 3> points;

    public:
        /// @brief Creates a 2D-triangle which vertices are the points passed
        Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3)
            : points{p1, p2, p3} {}

        const Vector2& operator[](size_t index)
        {
            return points[index];
        }
    };
}