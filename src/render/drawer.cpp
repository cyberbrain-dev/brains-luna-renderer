#include "drawer.h"

#include <cmath>

namespace luna
{
    void Drawer::fill(const luna::Color color) const noexcept
    {
        // looping through all the pixels...
        for (int y = 0; y < _window.height; y++)
        {
            for (int x = 0; x < _window.width; x++)
            {
                // ...and setting the color
                _window._colorBuffer[y * _window.width + x] = color.toUint32();
            }
        }
    }

    void Drawer::drawPixel(const int x, const int y, const luna::Color color) const noexcept
    {
        if (x >= 0 && x < _window.width && y >= 0 && y < _window.height)
        {
            _window._colorBuffer[y * _window.width + x] = color.toUint32();
        }
    }

    void Drawer::drawSolidGrid(const int cell_width, const int cell_height, const luna::Color color) const noexcept
    {
        for (int y = 0; y < _window.height; y++)
        {
            for (int x = 0; x < _window.width; x++)
            {
                if (y % cell_height == 0)
                {
                    _window._colorBuffer[y * _window.width + x] = color.toUint32();
                    continue;
                }

                if (x % cell_width == 0)
                {
                    _window._colorBuffer[y * _window.width + x] = color.toUint32();
                }
            }
        }
    }

    void Drawer::drawDottedGrid(const int cell_width, const int cell_height, const luna::Color color) const noexcept
    {
        for (int y = 0; y < _window.height; y += cell_height)
        {
            for (int x = 0; x < _window.width; x += cell_width)
            {
                _window._colorBuffer[y * _window.width + x] = color.toUint32();
            }
        }
    }

    void Drawer::drawRect(
        const int x_pos,
        const int y_pos,
        const int width,
        const int height,
        const luna::Color color) const noexcept
    {
        for (int y = y_pos; y < y_pos + height; y++)
        {
            for (int x = x_pos; x < x_pos + width; x++)
            {
                drawPixel(x, y, color);
            }
        }
    }

    void Drawer::drawLineDDA(
        const int x0,
        const int y0,
        const int x1,
        const int y1,
        const luna::Color color) const noexcept
    {
        const int delta_x = x1 - x0;
        const int delta_y = y1 - y0;

        // defining which of the sides is the longest
        const int longest_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

        const float x_inc = static_cast<float>(delta_x) / static_cast<float>(longest_side_length);
        const float y_inc = static_cast<float>(delta_y) / static_cast<float>(longest_side_length);

        auto current_x = static_cast<float>(x0);
        auto current_y = static_cast<float>(y0);

        for (int i = 0; i <= longest_side_length; i++)
        {
            drawPixel(static_cast<int>(std::round(current_x)), static_cast<int>(std::round(current_y)), color);
            current_x += x_inc;
            current_y += y_inc;
        }
    }

    void Drawer::drawLineBresenham(
        int x0,
        int y0,
        const int x1,
        const int y1,
        const luna::Color color) const noexcept
    {
        const int dx = abs(x1 - x0);
        const int dy = abs(y1 - y0);

        const int sx = (x0 < x1) ? 1 : -1;
        const int sy = (y0 < y1) ? 1 : -1;

        int err = dx - dy;

        while (true) {
            drawPixel(x0, y0, color); // drawing current pixel

            if (x0 == x1 && y0 == y1) break; // line is finished

            const int e2 = 2 * err;

            if (e2 > -dy)
            {
                err -= dy;
                x0 += sx;
            }

            if (e2 < dx)
            {
                err += dx;
                y0 += sy;
            }
        }
    }

    void Drawer::drawEmptyTriangle(const luna::Triangle& triangle, const luna::Color color) const noexcept
    {
        const luna::Vector2 p1 = triangle[0];
        const luna::Vector2 p2 = triangle[1];
        const luna::Vector2 p3 = triangle[2];

        // drawing lines between each of the vertices
        drawLineBresenham(static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y), color);
        drawLineBresenham(static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p3.x), static_cast<int>(p3.y), color);
        drawLineBresenham(static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p3.x), static_cast<int>(p3.y), color);
    }

    // Draw a filled triangle with the flat-top/flat-bottom method
    // We split the original triangle in two, half flat-bottom and half flat-top
    //
    //
    //          (x0,y0)
    //            / \
    //           /   \
    //          /     \
    //         /       \
    //        /         \
    //   (x1,y1)------(Mx,My)
    //       \_           \
    //          \_         \
    //             \_       \
    //                \_     \
    //                   \    \
    //                     \_  \
    //                        \_\
    //                           \
    //                         (x2,y2)
    //
    void Drawer::drawFilledTriangle(const Triangle& triangle, const Color color) const noexcept
    {
        // if x1 and x2 are equal, then the (x2, y2) is the M point itself...
        if (triangle[1].x == triangle[2].x)
        {
            // ...and only flat-bottom triangle should be drawn
            _drawFlatBottomTriangle(
                triangle[0].x,
                triangle[0].y,
                triangle[1].x,
                triangle[1].y,
                triangle[2].x,
                triangle[2].y,
                color
            );

            return;
        }

        // if x1 and x0 are equal, then the (x0, y0) is the M point itself...
        if (triangle[1].x == triangle[0].x)
        {
            // ...and only flat-top triangle should be drawn
            _drawFlatTopTriangle(
                triangle[1].x,
                triangle[1].y,
                triangle[0].x,
                triangle[0].y,
                triangle[2].x,
                triangle[2].y,
                color
            );
        }

        // calculating the Mx and My
        // (vertices of any triangle are sorted by Y when it is initialized)
        const float My = triangle[1].y;
        const float Mx = (triangle[2].x - triangle[0].x)
        * (triangle[1].y - triangle[0].y)
        / (triangle[2].y - triangle[0].y)
        + triangle[0].x;

        drawLineBresenham(
            static_cast<int>(triangle[1].x),
            static_cast<int>(triangle[1].y),
            static_cast<int>(Mx),
            static_cast<int>(My),
            color
        );
        _drawFlatBottomTriangle(
            triangle[0].x,
            triangle[0].y,
            triangle[1].x,
            triangle[1].y,
            Mx,
            My,
            color
        );
        _drawFlatTopTriangle(
            triangle[1].x,
            triangle[1].y,
            Mx,
            My,
            triangle[2].x,
            triangle[2].y,
            color
        );
    }

    // Draw a filled a triangle with a flat bottom
    //
    //        (x0,y0)
    //          / \
    //         /   \
    //        /     \
    //       /       \
    //      /         \
    //  (x1,y1)------(x2,y2)
    //
    void Drawer::_drawFlatBottomTriangle(
        const float x0,
        const float y0,
        const float x1,
        const float y1,
        const float x2,
        const float y2,
        const Color color) const noexcept
    {
        // calculating the two slopes (two triangle legs)
        const float slope1 = (x1 - x0) / (y1 - y0);
        const float slope2 = (x2 - x0) / (y2 - y0);

        // start and end of the first scanline
        float xStart = x0;
        float xEnd = x0;

        // loop through all the scanlines from top to bottom
        for (int y = static_cast<int>(y0); y < static_cast<int>(y2); y++)
        {
            drawLineBresenham(static_cast<int>(xStart), y, static_cast<int>(xEnd), y, color);
            xStart += slope1;
            xEnd += slope2;
        }
    }

    // Draw a filled a triangle with a flat top
    //
    //  (x0,y0)------(x1,y1)
    //      \         /
    //       \       /
    //        \     /
    //         \   /
    //          \ /
    //        (x2,y2)
    //
    void Drawer::_drawFlatTopTriangle(
        const float x0,
        const float y0,
        const float x1,
        const float y1,
        const float x2,
        const float y2,
        const Color color) const noexcept
    {
        // calculating the two slopes (two triangle legs)
        const float slope0 = (x2 - x0) / (y2 - y0);
        const float slope1 = (x2 - x1) / (y2 - y1);

        // start and end of the first scanline
        float xStart = x2;
        float xEnd = x2;

        // loop through all the scanlines from bottom to top
        for (int y = static_cast<int>(y2); y > static_cast<int>(y0); y--)
        {
            drawLineBresenham(static_cast<int>(xStart), y, static_cast<int>(xEnd), y, color);

            xStart -= slope0;
            xEnd -= slope1;
        }
    }
}
