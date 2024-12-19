#include "vector.h"

vector3_t vect3_rotate(vector3_t v, vector3_t rotation)
{
    vector3_t rotated_vector = vect3_rotate_x(v, rotation.x);
    rotated_vector = vect3_rotate_y(rotated_vector, rotation.y);
    rotated_vector = vect3_rotate_z(rotated_vector, rotation.z);

    return rotated_vector;
}

vector3_t vect3_rotate_x(vector3_t v, float angle)
{
    vector3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };

    return rotated_vector;
}

vector3_t vect3_rotate_y(vector3_t v, float angle)
{
    vector3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };

    return rotated_vector;
}

vector3_t vect3_rotate_z(vector3_t v, float angle)
{
    vector3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };

    return rotated_vector;
}