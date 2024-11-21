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
            color_buffer[y * window_width + x] = color;
        }
    }
}

