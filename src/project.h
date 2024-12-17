#ifndef PROJECT_H
#define PROJECT_H

#include "vector.h"

extern float fov_factor;

/// @brief Projects a 3D point in 2D
/// @param point 3D point
/// @returns A projected 2D-point 
vector2_t project(vector3_t point);

#endif