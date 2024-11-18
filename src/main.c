#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>


/// @brief SDL window instance
SDL_Window* window = NULL;
/// @brief SDL renderer instance
SDL_Renderer* renderer = NULL;

/// @brief Indicates whether the gameloop is running or not
bool is_running = false;


/// @brief Creates a simple Luna window
/// @return `true` - if the creation is successful, otherwise - `false`
bool initialize_window(void)
{
    // initializing SDL subsystems...
    if (SDL_INIT(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "An error occured initializing SDL subsystems.\n");
        return false;
    }


    // initializing a SDL window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_BORDERLESS
    );

    if (!window)
    {
        fprintf(stderr, "An error occured initializing SDL window.\n");
        return false;
    }


    // initializin SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        fprintf(stderr, "An error occured initializing SDL renderer.\n");
        return false;
    }


    return true;
}


int main()
{
    is_running = initialize_window();

    /* TODO: Make a gameloop */
}
