#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

/// @brief Represents a vector in a two-dimensional space
typedef struct
{
    float x;
    float y;
} vector2_t;

/// @brief Represents a vector in a three-dimensional space
typedef struct
{
    float x;
    float y;
    float z;
} vector3_t;


/// @brief Rotating the vector by three axis
/// @param v a vector to be rotated
/// @param rotation the vector of angles in radians
/// @return The result of rotating `v` vector
vector3_t vect3_rotate(vector3_t v, vector3_t rotation);


/// @brief Rotating the vector by X
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vector3_t vect3_rotate_x(vector3_t v, float angle);

/// @brief Rotating the vector by Y
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vector3_t vect3_rotate_y(vector3_t v, float angle);

/// @brief Rotating the vector by Z
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vector3_t vect3_rotate_z(vector3_t v, float angle);

#endif