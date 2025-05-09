#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

/// @brief Represent a 3D face, which has three integers as fields - indexes of vertices
typedef struct
{
    int a;
    int b;
    int c;
} face_t;


/// @brief Represents a 2D triangle
typedef struct
{
    vector2_t points[3];
} triangle_t;

#endif