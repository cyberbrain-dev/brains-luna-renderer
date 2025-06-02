#pragma once

#include "core/colors.h"

#include "engine/triangle.h"

#include "render/window.h"

namespace luna
{
    class Drawer
    {
        Window& _window;

    public:
        explicit Drawer(Window& window)
            : _window(window) {}

        /// @brief Fills the window with the color passed
        /// @param color the window will be filled by this color
        void fill(luna::Color color) const noexcept;
        /// @brief Sets a single pixel with the color provided
        /// @param x x of the pixel
        /// @param y y of the pixel
        /// @param color a color for the pixel to be set
        void drawPixel(int x, int y, luna::Color color) const noexcept;
        /// @brief Draws a solid grid
        /// @param cell_width cell's width
        /// @param cell_height cell's height
        /// @param color a color of the grid
        void drawSolidGrid(int cell_width, int cell_height, luna::Color color) const noexcept;
        /// @brief Draws a dotted grid with cell sizes provided
        /// @param cell_width cell's width
        /// @param cell_height cell's height
        /// @param color a color of the grid
        void drawDottedGrid(int cell_width, int cell_height, luna::Color color) const noexcept;
        /// @brief Draws a rectangle
        /// @param x_pos X of the rectangle
        /// @param y_pos Y of the rectangle
        /// @param width rectangle's width
        /// @param height rectangle's height
        /// @param color rectangle's color
        void drawRect(int x_pos, int y_pos, int width, int height, luna::Color color) const noexcept;
        /// @brief Draws a line using DDA algorithm
        void drawLineDDA(int x0, int y0, int x1, int y1, luna::Color color) const noexcept;
        /// @brief Draws a line using Bresenham's algorithm
        void drawLineBresenham(int x0, int y0, int x1, int y1, luna::Color color) const noexcept;
        /// @brief Draws a trangle
        void drawEmptyTriangle(const luna::Triangle &triangle, luna::Color color) const noexcept;
    };
}
