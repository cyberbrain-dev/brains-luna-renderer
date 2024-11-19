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
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
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

/// @brief Sets up a program before the render loop
void setup(void)
{

}
/// @brief Checking any input the user does 
void process_input(void)
{
    // Creating and polling the current moment event
    SDL_Event current_event;
    SDL_PollEvent(&current_event);

    // Determining the type of the event
    switch (current_event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (current_event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;

            break;
    }

}
/// @brief Updates the states of the different objects in program 
void update(void)
{

}
/// @brief Renders the frame 
void render(void)
{
    // Setting a base color for "empty frame"...
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    // ... and clearing the frame before another render
    SDL_RenderClear(renderer);


    // Updating the screen
    SDL_RenderPresent(renderer);
}


int main()
{
    is_running = initialize_window();


    // A simple game loop is down there...
    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }


    return 0;
}
