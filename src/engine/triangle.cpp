#include "triangle.h"

#include <algorithm>

namespace luna
{
    Triangle::Triangle(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) noexcept
        : _points{p1, p2, p3}
    {
        _sortPointByYAscending();
    }

    void Triangle::_sortPointByYAscending()
    {
        std::sort(
            _points.begin(),
            _points.end(),
            [](const Vector2& a, const Vector2& b)
            {
                return a.y < b.y;
            }
        );
    }
}
