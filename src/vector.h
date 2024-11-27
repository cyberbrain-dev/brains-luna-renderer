#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

/// @brief Represents a vector in a two-dimensional space
typedef struct
{
    float x;
    float y;
} vect2_t;

/// @brief Represents a vector in a three-dimensional space
typedef struct
{
    float x;
    float y;
    float z;
} vect3_t;


/// @brief Rotating the vector by X
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vect3_t vect3_rotate_x(vect3_t v, float angle);

/// @brief Rotating the vector by Y
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vect3_t vect3_rotate_y(vect3_t v, float angle);

/// @brief Rotating the vector by Z
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vect3_t vect3_rotate_z(vect3_t v, float angle);

#endif