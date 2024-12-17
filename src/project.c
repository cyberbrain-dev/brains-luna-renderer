#include "project.h"

float fov_factor = 640;

vector2_t project(vector3_t point)
{
    vector2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z
    };

    return projected_point;
}
