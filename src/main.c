#define VECTOR_TEST // For the cube
#define NUMBER_OF_POINTS 9 * 9 * 9

#include <stdbool.h>

#include "display.h"
#include "draw.h"
#include "lunacolors.h"
#include "vector.h"


#ifdef VECTOR_TEST

vect3_t cube_points[NUMBER_OF_POINTS]; // A test 9x9x9 cube

#endif /* VECTOR_TEST */ 

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

    #ifdef VECTOR_TEST

    // start loading my array of cube vectors
    // from -1 to 1 (in this 9x9x9 cube)
    int cube_array_counter = 0;

    for (float x = -1; x <= 1; x += 0.25f)
    {
        for (float y = -1; y <= 1; y += 0.25f)
        {
            for (float z = -1; z <= 1; z += 0.25f)
            {
                // creating a new vector and putting it in the cube array
                vect3_t new_point = { x, y, z };
                cube_points[cube_array_counter] = new_point;

                // moving to the next point in the cube
                cube_array_counter++;
            }
        }
    }

    #endif /* VECTOR_TEST */
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
