#define NUMBER_OF_POINTS 9 * 9 * 9

#include <stdbool.h>

#include "display.h"
#include "draw.h"
#include "lunacolors.h"
#include "vector.h"


vect3_t cube_points[NUMBER_OF_POINTS]; // A test 9x9x9 cube
vect2_t projected_cube_points[NUMBER_OF_POINTS]; // projected points for the cube

// position of the camera
vect3_t camera_position = { 0, 0, -5 };
// Test rotating
vect3_t cube_rotation = { 0, 0, 0 };

float fov_factor = 640;

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

/// @brief Projects a 3D point in 2D
/// @param point 3D point
/// @returns A projected 2D-point 
vect2_t project(vect3_t point)
{
    vect2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z
    };

    return projected_point;
}

/// @brief Updates the states of the different objects in program 
void update(void)
{
    // rotating the cube
    cube_rotation.x += 0.008;
    cube_rotation.y += 0.008;
    cube_rotation.z += 0.009;

    // projecting all the points of the cube
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        vect3_t point = cube_points[i];

        vect3_t transformed_point = vect3_rotate(point, cube_rotation);

        // translating the cube a little bit farther
        transformed_point.z -= camera_position.z;

        vect2_t projected_point = project(transformed_point);

        projected_cube_points[i] = projected_point;
    }
}

/// @brief Renders the frame 
void render(void)
{
    draw_dotted_grid(10, 10, LUNA_COLOR_GREY);

    // loop through all the projected point and rendering them
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        // current point
        vect2_t projected_point = projected_cube_points[i];

        draw_rect(
            projected_point.x + (window_width / 2),
            projected_point.y + (window_height / 2),
            4,
            4,
            LUNA_COLOR_YELLOW
        );
    }

    // preparing the color buffer to render
    // * after that the color buffer can be modified without impact on rendering target
    translate_color_buffer();

    // clearing the color buffer after putting it to the rendering target
    fill_color_buffer(LUNA_COLOR_BLACK);

    // updating the screen
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
