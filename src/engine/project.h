#pragma once

#include "engine/vector.h"

extern float fov_factor;

/// @brief Projects a 3D point in 2D perspectively
/// @param point 3D point
/// @returns A projected 2D-point 
luna::Vector2 project_perspective(luna::Vector3 point);

/// @brief Projects a 3D point in 2D orthographicly
/// @param point 3D point
/// @returns A projected 2D-point 
luna::Vector2 project_orthographic(luna::Vector3 point);