#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

// SDL window instance
SDL_Window* window = NULL;
// SDL renderer instance
SDL_Renderer* renderer = NULL;

// An array, representing color buffer - a collection of pixel colors, that should be rendered
uint32_t* color_buffer = NULL;

const int window_width = 800;
const int window_height = 600;

// Indicates whether the gameloop is running or not
bool is_running = false;


// Creates a simple Luna window
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
        window_width,
        window_height,
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

// Sets up a program before the render loop
void setup(void)
{
    // allocating memory in color buffer for each pixel of the window
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
}
// Checking any input the user does 
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
// Updates the states of the different objects in program 
void update(void)
{

}
// Renders the frame 
void render(void)
{
    // Setting a base color for "empty frame"...
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    // ... and clearing the frame before another render
    SDL_RenderClear(renderer);


    // Updating the screen
    SDL_RenderPresent(renderer);
}

// Releases all the resources the window has been using
void destroy_window(void)
{
    free(color_buffer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
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

    destroy_window();


    return 0;
}
