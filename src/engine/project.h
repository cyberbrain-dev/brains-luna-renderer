#pragma once

#include "vector.h"

extern float fov_factor;

/// @brief Projects a 3D point in 2D perspectively
/// @param point 3D point
/// @returns A projected 2D-point 
vector2_t project_perspective(vector3_t point);

/// @brief Projects a 3D point in 2D orthographicly
/// @param point 3D point
/// @returns A projected 2D-point 
vector2_t project_orthographic(vector3_t point);