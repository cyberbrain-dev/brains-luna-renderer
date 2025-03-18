#ifndef MESH_H
#define MESH_H

#include <stdio.h>

#include "../lib/clist/list.h"

#include "triangle.h"
#include "vector.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES 12     // 2 triangles per each of 6 cube faces

/// @brief Represents a 3D-mesh
typedef struct
{
    /// @brief dynamic list of 3D-vectors
    list_t* vertices;

    /// @brief dynamic list of faces
    list_t* faces;

    /// @brief mesh's rotation
    vector3_t rotation;
} mesh_t;

/// @brief An array of vertices of the test cube
extern vector3_t cube_vertices[N_CUBE_VERTICES];

/// @brief Array of faces of the test cube
extern face_t cube_faces[N_CUBE_FACES];

/// @brief The mesh that is being rendered during the application works
extern mesh_t mesh;


/// @brief Initializes the lists in the mesh
void mesh_init(void);
/// @brief Loads a cube data to the mesh
void mesh_load_cube(void);

#endif