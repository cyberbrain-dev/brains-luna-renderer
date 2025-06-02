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

        // defining which of the sides is the longes
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
}
