#include "vector.h"

vect3_t vect3_rotate_x(vect3_t v, float angle)
{
    vect3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };

    return rotated_vector;
}

vect3_t vect3_rotate_y(vect3_t v, float angle)
{
    vect3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };

    return rotated_vector;
}

vect3_t vect3_rotate_z(vect3_t v, float angle)
{
    vect3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };

    return rotated_vector;
}