#ifndef MESH_H
#define MESH_H

#include "triangle.h"
#include "vector.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES 12     // 2 triangles per each of 6 cube faces

/// @brief An array of vertices of the test cube
extern vector3_t mesh_vertices[N_MESH_VERTICES];


/// @brief Array of faces of the test cube
extern face_t mesh_faces[N_MESH_FACES];

#endif