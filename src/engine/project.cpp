#include "project.h"

float fov_factor_perspective = 640;
float fov_factor_orthographic = 128;

luna::Vector2 project_perspective(const luna::Vector3& point)
{
    const luna::Vector2 projected_point{
        (fov_factor_perspective * point.x) / point.z,
        (fov_factor_perspective * point.y) / point.z
    };

    return projected_point;
}

luna::Vector2 project_orthographic(const luna::Vector3& point)
{
    const luna::Vector2 projected_point = {
        fov_factor_orthographic * point.x,
        fov_factor_orthographic * point.y
    };

    return projected_point;
}
