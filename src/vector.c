#include "vector.h"

// Vector2 operations

float vector2_length(vector2_t v)
{
    return sqrt(v.x * v.x + v.y + v.y);
}

vector2_t vector2_add(vector2_t v1, vector2_t v2)
{
    vector2_t result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}
vector2_t vector2_sub(vector2_t v1, vector2_t v2)
{
    vector2_t result = {v1.x - v2.x, v1.y - v2.y};
    return result;
}
float vector2_sclpr(vector2_t v1, vector2_t v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y); 
}



// Vector3 operations

float vector3_length(vector3_t v)
{
    return sqrt(v.x * v.x + v.y + v.y + v.z * v.z);
}

vector3_t vector3_add(vector3_t v1, vector3_t v2)
{
    vector3_t result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return result;
}
vector3_t vector3_sub(vector3_t v1, vector3_t v2)
{
    vector3_t result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}
float vector3_sclpr(vector3_t v1, vector3_t v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z); 
}

vector3_t vector3_rotate(vector3_t v, vector3_t rotation)
{
    vector3_t rotated_vector = vector3_rotate_x(v, rotation.x);
    rotated_vector = vector3_rotate_y(rotated_vector, rotation.y);
    rotated_vector = vector3_rotate_z(rotated_vector, rotation.z);

    return rotated_vector;
}
vector3_t vector3_rotate_x(vector3_t v, float angle)
{
    vector3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };

    return rotated_vector;
}
vector3_t vector3_rotate_y(vector3_t v, float angle)
{
    vector3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };

    return rotated_vector;
}
vector3_t vector3_rotate_z(vector3_t v, float angle)
{
    vector3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };

    return rotated_vector;
}