#include "display.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;


bool initialize_window(void)
{
    // initializing SDL subsystems...
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Luna: An error occured initializing SDL subsystems.\n");
        return false;
    }

#ifndef LUNA_DEBUG
    // using the SDL to query the resolution of my monitor...
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    // ...and setting the resolution 
    window_width = display_mode.w;
    window_height = display_mode.h;
#endif


    // initializing a SDL window
    window = SDL_CreateWindow(
        "Luna Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        0
    );

    if (!window)
    {
        fprintf(stderr, "Luna: An error occured initializing SDL window.\n");
        return false;
    }


    // initializin SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        fprintf(stderr, "Luna: An error occured initializing SDL renderer.\n");
        return false;
    }

#ifndef LUNA_DEBUG
    // setting the window fullscreen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
#endif


    return true;
}
void destroy_window(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void translate_color_buffer(void)
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int) (window_width * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
