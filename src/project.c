#include "project.h"

float fov_factor_perspective = 640;
float fov_factor_orthographic = 128;

vector2_t project_perspective(vector3_t point)
{
    vector2_t projected_point = {
        .x = (fov_factor_perspective * point.x) / point.z,
        .y = (fov_factor_perspective * point.y) / point.z
    };

    return projected_point;
}

vector2_t project_orthographic(vector3_t point)
{
    vector2_t projected_point = {
        .x = (fov_factor_orthographic * point.x),
        .y = (fov_factor_orthographic * point.y)
    };

    return projected_point;
}
