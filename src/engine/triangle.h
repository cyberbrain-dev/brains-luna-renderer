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

        /// @brief Creates a face
        Face() noexcept = default;

        /// @brief Creates a face. The parameters 
        /// that you have to pass in this constructor are indices of vertices
        Face(const int a, const int b, const int c) noexcept
            : a{a}, b{b}, c{c} {}
    };
    
    /// @brief Represents a 2D triangle
    struct Triangle
    {
    private:
        std::array<luna::Vector2, 3> _points;

        bool _isSortedByY{false};

    public:
        /// @brief Creates a 2D-triangle with zero vectors
        Triangle() = default;

        /// @brief Creates a 2D-triangle which vertices are the points passed
        Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3) noexcept
            : _points{p1, p2, p3} {}


        /// @brief Returns the point at the index passed
        const Vector2& operator[](const size_t index) const
        {
            return _points[index];
        }

        /// @brief Returns the M point. The line from (x1, y1) to (mX, mY) divides the triangle into 2 pieces:
        /// flat-bottom and flat-top triangles
        /// @attention This method may call points sorting method, so getPointM() method does change the object
        Vector2 getPointM() noexcept;

    private:
        /// @brief Sorts the points in the points array by y ascending
        void _sortPointsByYAscending() noexcept;
    };
}