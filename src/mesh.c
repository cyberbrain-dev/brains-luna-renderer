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

void mesh_init(void) 
{
    mesh.vertices = list_create(sizeof(vector3_t), 6);
    mesh.faces = list_create(sizeof(face_t), 6);
}

void mesh_load_cube(void) 
{
    // looping through all the cube vertices
    for (int i = 0; i < N_CUBE_VERTICES; i++)
    {
        vector3_t vertex = cube_vertices[i];
        list_add(mesh.vertices, &vertex);
    }

    // looping through all the cube faces
    for (int i = 0; i < N_CUBE_FACES; i++)
    {
        face_t face = cube_faces[i];
        list_add(mesh.faces, &face);
    }
}