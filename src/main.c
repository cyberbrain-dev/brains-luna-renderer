#include <stdbool.h>

#include "display.h"
#include "draw.h"

#include "lunacolors.h"


/// @brief Indicates whether the gameloop is running or not
bool is_running = false;


/// @brief Sets up a program before the render loop
void setup(void)
{
    // allocating memory in color buffer for each pixel of the window
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // creating SDL texture
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
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
    // ... and clearing the rendering target before another render
    SDL_RenderClear(renderer);

    fill_color_buffer(LUNA_COLOR_BLACK);
    draw_pixel(45, 206, LUNA_COLOR_RED);

    // preparing the color buffer to render
    // * after that the color buffer can be modified without impact on rendering target
    translate_color_buffer();


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

    destroy_window();


    return 0;
}
