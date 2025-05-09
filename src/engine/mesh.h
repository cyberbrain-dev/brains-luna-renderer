#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "triangle.h"
#include "vector.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES 12     // 2 triangles per each of 6 cube faces

/// @brief Represents a 3D-mesh
typedef struct
{
    /// @brief dynamic vector of 3D-vectors
    std::vector<luna::Vector3> vertices;

    /// @brief dynamic vector of faces
    std::vector<face_t> faces;

    /// @brief mesh's rotation
    luna::Vector3 rotation;
} mesh_t;

/// @brief An array of vertices of the test cube
extern luna::Vector3 cube_vertices[N_CUBE_VERTICES];

/// @brief Array of faces of the test cube
extern face_t cube_faces[N_CUBE_FACES];

/// @brief The mesh that is being rendered during the application works
extern mesh_t mesh;


/// @brief Loads a cube data to the mesh
/// @attention `mesh_init` FUNCTION MUST BE CALLED BEFORE
void mesh_load_cube(void);
/// @brief Loads a mesh from the OBJ file
/// @param filepath a path to the file
/// @attention `mesh_init` FUNCTION MUST BE CALLED BEFORE
void mesh_load_obj(const char* filepath);