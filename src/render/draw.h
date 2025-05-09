#pragma once

#include <stdint.h>
#include <math.h>

#include "display.h"
#include "engine/triangle.h"

/// @brief Fills the color buffer with the color passed
/// @param color the window will be filled by this color
void fill_color_buffer(uint32_t color);
/// @brief Sets a single pixel with the color provided
/// @param x x of the pixel
/// @param y y of the pixel
/// @param color a color for the pixel to be set
void draw_pixel(int x, int y, uint32_t color);
/// @brief Draws a solid grid
/// @param cell_width cell's width
/// @param cell_height cell's height
/// @param color a color of the grid
void draw_solid_grid(int cell_width, int cell_height, uint32_t color);
/// @brief Draws a dotted grid with cell sizes provided
/// @param cell_width cell's width
/// @param cell_height cell's height
/// @param color a color of the grid
void draw_dotted_grid(int cell_width, int cell_height, uint32_t color);
/// @brief Draws a rectangle
/// @param x_pos X of the rectangle
/// @param y_pos Y of the rectangle
/// @param width rectangle's width
/// @param height rectangle's height
/// @param color rectangle's color
void draw_rect(int x_pos, int y_pos, int width, int height, uint32_t color);
/// @brief Draws a line using DDA algorithm
void draw_line_dda(int x0, int y0, int x1, int y1, uint32_t color);
/// @brief Draws a line using Bresenham's algorithm
void draw_line_bresenham(int x0, int y0, int x1, int y1, uint32_t color);
/// @brief Draws a trangle
void draw_empty_triangle(triangle_t triangle, uint32_t color);
