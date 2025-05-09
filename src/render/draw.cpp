#include "draw.h"


void fill_color_buffer(uint32_t color)
{
    // looping through all the pixels...
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            // ...and setting the color
            color_buffer[y * window_width + x] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color)
{
    if (x >= 0 && 
        x < window_width && 
        y >= 0 && 
        y < window_height)
    {
        color_buffer[y * window_width + x] = color;
    }
}

void draw_solid_grid(int cell_width, int cell_height, uint32_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            if (y % cell_height == 0)
            {
                color_buffer[y * window_width + x] = color;
                continue;
            }

            if (x % cell_width == 0)
            {
                color_buffer[y * window_width + x] = color;
            }
        }
    }
}

void draw_dotted_grid(int cell_width, int cell_height, uint32_t color)
{
    for (int y = 0; y < window_height; y += cell_height)
    {
        for (int x = 0; x < window_width; x += cell_width)
        {
            color_buffer[y * window_width + x] = color;
        }
    }
}

void draw_rect(int x_pos, int y_pos, int width, int height, uint32_t color)
{
    for (int y = y_pos; y < y_pos + height; y++)
    {
        for (int x = x_pos; x < x_pos + width; x++)
        {
            draw_pixel(x, y, color);
        }
    }
}

void draw_line_dda(int x0, int y0, int x1, int y1, uint32_t color)
{
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;

    // defining which of the sides is the longes
    int longest_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

    float x_inc = delta_x / (float)longest_side_length;
    float y_inc = delta_y / (float)longest_side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= longest_side_length; i++)
    {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void draw_line_bresenham(int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        draw_pixel(x0, y0, color); // drawing current pixel

        if (x0 == x1 && y0 == y1) break; // line is finished

        int e2 = 2 * err;

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

void draw_empty_triangle(triangle_t triangle, uint32_t color)
{
    luna::Vector2 p1 = triangle.points[0];
    luna::Vector2 p2 = triangle.points[1];
    luna::Vector2 p3 = triangle.points[2];

    // drawing lines between each of the vertices 
    draw_line_bresenham(p1.x, p1.y, p2.x, p2.y, color);
    draw_line_bresenham(p2.x, p2.y, p3.x, p3.y, color);
    draw_line_bresenham(p1.x, p1.y, p3.x, p3.y, color);
}