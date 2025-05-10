#include <string.h>
#include <string>
#include <vector>
#include <array>

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
std::string pathToModel;

/// @brief vector of the triangles to be rendered
std::vector<luna::Triangle> triangles_to_render;

// position of the camera
luna::Vector3 camera_position{ 0, 0, 0 };

/// @brief Indicates whether the gameloop is running or not
bool is_running = false;

int previous_frame_time = 0;

luna::Mesh mesh;

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

    mesh = luna::Mesh::load(pathToModel);
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
        luna::Face current_face = mesh.faces[i];

        // getting vertices of current face
        luna::Vector3 current_face_vertices[3] = {
            mesh.vertices[current_face.a - 1],
            mesh.vertices[current_face.b - 1],
            mesh.vertices[current_face.c - 1],
        };

        // a little array that'll help us to save the transformed vertices
        luna::Vector3 transformed_vertices[3];

        // looping through all three vertices of this current face to apply transformations
        for (int j = 0; j < 3; j++)
        {
            luna::Vector3 transformed_vertex = current_face_vertices[j];

            // applying the rotation
            transformed_vertex = transformed_vertex.rotate(mesh.rotation);

            // moving all the vertices a bit "inside" the monitor
            transformed_vertex.z += 5;

            // saving the vertex
            transformed_vertices[j] = transformed_vertex;
        }

        luna::Vector3 a = transformed_vertices[0];    /*   a   */
        luna::Vector3 b = transformed_vertices[1];    /*  / \  */ 
        luna::Vector3 c = transformed_vertices[2];    /* c---b */

        // getting two vectors of the face to find the cross product (face normal)
        luna::Vector3 ab = b - a;
        luna::Vector3 ac = c - a;

        // computing the face normal
        luna::Vector3 normal = luna::Vector3::cross(ab, ac);
        normal.normalize();

        // finding the vector between a point in the triangle and the camera origin
        luna::Vector3 camera_ray = camera_position - a;

        // bypass the triangle if it is looking away from the camera
        if (luna::Vector3::dot(normal, camera_ray) < 0) 
            continue;


        // an array which staores all the projected points of current triangle
        std::array<luna::Vector2, 3> projectedVertices{};

        // looping through all three vertices to perform projection
        for (int j = 0; j < 3; j++)
        {
            // projecting the transformed point
            luna::Vector2 projected_vertex = project_perspective(transformed_vertices[j]);

            // scale and translating projected points to the middle of the screen
            projected_vertex.x += window_width / 2;
            projected_vertex.y += window_height / 2;

            // setting the projected vertex to triangle's point
            projectedVertices[j] = projected_vertex;
        }

        luna::Triangle projectedTriangle(
            projectedVertices[0], 
            projectedVertices[1], 
            projectedVertices[2]
        );

        // saving the projected triangle to be rendered
        triangles_to_render.push_back(projectedTriangle);
    }
}

/// @brief Renders the frame 
void render(void)
{
    draw_dotted_grid(10, 10, luna::colorGrey);

    for (int i = 0; i < triangles_to_render.size(); i++)
    {
        draw_empty_triangle(triangles_to_render[i], luna::colorCyan);
    }

    // clearing the vector of triangles to render as we've already rendered everything
    triangles_to_render.clear();

    // preparing the color buffer to render
    // after that the color buffer can be modified without impact on rendering target
    translate_color_buffer();

    // clearing the color buffer after putting it to the rendering target
    fill_color_buffer(luna::colorBlack);

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
        pathToModel = argv[2];
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
