#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>


#define FRAME_RATE 165
#define FRAME_TARGET_TIME (1000 / FRAME_RATE)


/// @brief SDL window instance
extern SDL_Window* window;
/// @brief SDL renderer instance
extern SDL_Renderer* renderer;

/// @brief An array, representing color buffer - a collection of pixel colors, that should be rendered
extern uint32_t* color_buffer;
/// @brief A texture that the color buffer is translated to and which is able to be rendered by SDL
extern SDL_Texture* color_buffer_texture;

/// @brief Window width
extern int window_width;
/// @brief Window height
extern int window_height;


/// @brief Creates a simple Luna window
/// @return `true` if the initialization is successful, otherwise - `false`
bool initialize_window(void);

/// @brief Releases all the resources the window has been using
void destroy_window(void);

/// @brief Updates the SDL texture with our color buffer and copies the texture to the rendering target
void translate_color_buffer(void);

#endif