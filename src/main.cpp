#include <string.h>
#include <vector>

#include "render/display.h"
#include "render/draw.h"

#include "core/colors.h"

#include "engine/project.h"
#include "engine/vector.h"
#include "engine/mesh.h"

#ifndef LUNA_VERSION
#define LUNA_VERSION "1.0.0"
#endif

/// @brief Contains a path to the model that must be displayed 
///        during the work of application
const char* path_to_model = NULL;

/// @brief vector of the triangles to be rendered
std::vector<triangle_t> triangles_to_render;

// position of the camera
vector3_t camera_position = { 0, 0, 0 };

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

#ifdef LUNA_DEBUG
    // setting up the mesh
    mesh_load_obj("../assets/cube.obj");
#else
    // setting up the mesh
    mesh_load_obj(path_to_model);
#endif
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
    // if we have rendered everything kinda fast, 
    // we should wait until the time for rendering another frame comes
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME))

    previous_frame_time = SDL_GetTicks();

    // initializing a vector of the triangles to be rendered

    // rotating the cube
    mesh.rotation.x += 0.005;
    mesh.rotation.y += 0.005;
    mesh.rotation.z += 0.005;

    // looping through all the triangles of the mesh
    for (int i = 0; i < mesh.faces.size(); i++)
    {
        // getting current face
        face_t current_face = mesh.faces[i];

        // getting vertices of current face
        vector3_t current_face_vertices[3] = {
            mesh.vertices[current_face.a - 1],
            mesh.vertices[current_face.b - 1],
            mesh.vertices[current_face.c - 1],
        };

        // a little array that'll help us to save the transformed vertices
        vector3_t transformed_vertices[3];

        // looping through all three vertices of this current face to apply transformations
        for (int j = 0; j < 3; j++)
        {
            vector3_t transformed_vertex = current_face_vertices[j];

            // applying the rotation
            transformed_vertex = vector3_rotate(transformed_vertex, mesh.rotation);

            // moving all the vertices a bit "inside" the monitor
            transformed_vertex.z += 5;

            // saving the vertex
            transformed_vertices[j] = transformed_vertex;
        }

        vector3_t a = transformed_vertices[0];    /*   a   */
        vector3_t b = transformed_vertices[1];    /*  / \  */ 
        vector3_t c = transformed_vertices[2];    /* c---b */

        // getting two vectors of the face to find the cross product (face normal)
        vector3_t ab = vector3_sub(b, a);
        vector3_t ac = vector3_sub(c, a);

        // computing the face normal
        vector3_t normal = vector3_crosspr(ab, ac);
        vector3_normalize(&normal);

        // finding the vector between a point in the triangle and the camera origin
        vector3_t camera_ray = vector3_sub(camera_position, a);

        // bypass the triangle if it is looking away from the camera
        if (vector3_dotpr(normal, camera_ray) < 0) 
            continue;

        // a 2d triangle with projected vertices
        triangle_t projected_triangle;

        // looping through all three vertices to perform projection
        for (int j = 0; j < 3; j++)
        {
            // projecting the transformed point
            vector2_t projected_vertex = project_perspective(transformed_vertices[j]);

            // scale and translating projected points to the middle of the screen
            projected_vertex.x += window_width / 2;
            projected_vertex.y += window_height / 2;

            // setting the projected vertex to triangle's point
            projected_triangle.points[j] = projected_vertex;
        }

        // saving the projected triangle to be rendered
        triangles_to_render.push_back(projected_triangle);
    }
}

/// @brief Renders the frame 
void render(void)
{
    draw_dotted_grid(10, 10, LUNA_COLOR_GREY);

    for (int i = 0; i < triangles_to_render.size(); i++)
    {
        draw_empty_triangle(triangles_to_render[i], LUNA_COLOR_YELLOW);
    }

    // clearing the vector of triangles to render as we've already rendered everything
    triangles_to_render.clear();

    // preparing the color buffer to render
    // after that the color buffer can be modified without impact on rendering target
    translate_color_buffer();

    // clearing the color buffer after putting it to the rendering target
    fill_color_buffer(LUNA_COLOR_BLACK);

    // updating the screen
    SDL_RenderPresent(renderer);
}


/// @brief Releases all the vectors (dynamic arrays) used in the app
void free_resources(void)
{
    free(color_buffer);
}


int main(int argc, const char** argv)
{
    // parsing arguments of program
    if (argc == 2 && strcmp(argv[1], "-version") == 0) 
    {
        printf("Luna Renderer v%s\n", LUNA_VERSION);
        printf("© 2025 Cyberbrain. All Rights Reserved.\n");
        exit(0);
    }
    else if (argc == 3 && strcmp(argv[1], "-m") == 0)
    {
        path_to_model = argv[2];
    }
    else
    {
        fprintf(stderr, "Luna: Invalid arguments.\n");
        exit(-1);
    }

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
