#include "triangle.h"

#include <algorithm>

namespace luna
{
    Vector2 Triangle::getPointM() noexcept
    {
        // saving the time in case the points are already sorted
        if (!_isSortedByY)
            _sortPointsByYAscending();

        // getting the mX (by the formula) and mY
        const float mY = _points[1].y;
        const float mX = _points[0].x + (
            _points[2].x - _points[0].x)
            *
            (_points[1].y - _points[0].y)
            /
            (_points[2].y - _points[0].y);

        // returning the result vector
        return Vector2{mX, mY};
    }

    void Triangle::_sortPointsByYAscending() noexcept
    {
        // Sorting array by
        std::sort(
            _points.begin(),
            _points.end(),
            [](const luna::Vector2& v1, const luna::Vector2& v2)
            {
                return v1.y < v2.y;
            }
        );

        _isSortedByY = true;
    }
}