#include <stdbool.h>

#include "display.h"
#include "draw.h"

#include "lunacolors.h"

#include "project.h"
#include "vector.h"
#include "mesh.h"


triangle_t triangles_to_render[N_MESH_FACES];

// position of the camera
vector3_t camera_position = { 0, 0, -5 };
// Test rotating
vector3_t cube_rotation = { 0, 0, 0 };

/// @brief Indicates whether the gameloop is running or not
bool is_running = false;

int previous_frame_time = 0;


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
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    if (time_to_wait >= 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    // rotating the cube
    cube_rotation.x += 0.005;
    cube_rotation.y += 0.005;
    cube_rotation.z += 0.005;

    // looping through all the triangles of the mesh
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        face_t current_face = mesh_faces[i];

        // getting vertices of current face
        vector3_t current_face_vertices[3] = {
            mesh_vertices[current_face.a - 1],
            mesh_vertices[current_face.b - 1],
            mesh_vertices[current_face.c - 1]
        };


        // a 2d triangle with projected vertices
        triangle_t projected_triangle;

        // looping through all three vertices of this current face to apply transformations
        for (int j = 0; j < 3; j++)
        {
            vector3_t transformed_vertex = current_face_vertices[j];

            transformed_vertex = vect3_rotate(transformed_vertex, cube_rotation);

            // translating the vertex away from the camera
            transformed_vertex.z -= camera_position.z;

            // projecting the transformed point
            vector2_t projected_vertex = project_perspective(transformed_vertex);

            // scale and translating projected points to the middle of the screen
            projected_vertex.x += window_width / 2;
            projected_vertex.y += window_height / 2;

            // setting the projected vertex to triangle's point
            projected_triangle.points[j] = projected_vertex;
        }

        // saving the projected triangle to be rendered
        triangles_to_render[i] = projected_triangle;
    }
}

/// @brief Renders the frame 
void render(void)
{
    draw_dotted_grid(10, 10, LUNA_COLOR_GREY);

    for (int i = 0; i < N_MESH_FACES; i++)
    {
        draw_empty_triangle(triangles_to_render[i], LUNA_COLOR_YELLOW);
    }

    // preparing the color buffer to render
    // after that the color buffer can be modified without impact on rendering target
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
