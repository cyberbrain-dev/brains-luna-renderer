#include "mesh.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces    = NULL,
    .rotation = { 0, 0, 0 } 
};

vector3_t cube_vertices[N_CUBE_VERTICES] = {
    { -1, -1, -1 }, // 1
    { -1,  1, -1 }, // 2
    {  1,  1, -1 }, // 3
    {  1, -1, -1 }, // 4
    {  1,  1,  1 }, // 5
    {  1, -1,  1 }, // 6
    { -1,  1,  1 }, // 7
    { -1, -1,  1 }  // 8
};

face_t cube_faces[N_CUBE_FACES] = {
    // front
    { 1, 2, 3 },
    { 1, 3, 4 },

    // right
    { 4, 3, 5 },
    { 4, 5, 6 },

    // back
    { 6, 5, 7 },
    { 6, 7, 8 },

    // left
    { 8, 7, 2 },
    { 8, 2, 1 },

    // top
    { 2, 7, 5 },
    { 2, 5, 3 },

    // bottom
    { 6, 8, 1 },
    { 6, 1, 4 }
};

void mesh_load_cube(void) 
{
    // looping through all the cube vertices
    for (int i = 0; i < N_CUBE_VERTICES; i++)
    {
        vector3_t vertex = cube_vertices[i];
        list_push(mesh.vertices, vertex);
    }

    // looping through all the cube faces
    for (int i = 0; i < N_CUBE_FACES; i++)
    {
        face_t face = cube_faces[i];
        list_push(mesh.faces, face);
    }
}

void mesh_load_obj(const char* filepath)
{
    // getting the obj file 
    FILE* obj_file = fopen(filepath, "r");
    // if something went wrong...
    if (obj_file == NULL)
    {
        // ...we would print an error...
        fprintf(stderr, "Luna: Cannot read the model file. Check the path and ensure that the file exists.\n");

        // ..and quit the program
        exit(-1);
    }

    // a string that contains info whether about a vertex or a face
    char current_str[256];

    // reading all the strings in the obj file
    while (fgets(current_str, sizeof(current_str), obj_file) != NULL)
    {
        // if this is a vertex...
        if (strncmp(current_str, "v ", 2) == 0)
        {
            // creating a vertex
            vector3_t vertex;

            // reading the vertex data
            sscanf(
                current_str, 
                "v %f %f %f", 
                &vertex.x, 
                &vertex.y, 
                &vertex.z
            );

            list_push(mesh.vertices, vertex);
        }
        else if (strncmp(current_str, "f ", 2) == 0)
        {
            // creating a face
            face_t face;

            sscanf(
                current_str,
                "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
                &face.a,
                &face.b,
                &face.c
            );

            list_push(mesh.faces, face);
        }
    }
}