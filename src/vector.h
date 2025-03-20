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

#pragma region Vector2 operations

/// @brief Returns a length of 2D-vector
float vector2_length(vector2_t v);

/// @brief Sums two 2D-vectors
vector2_t vector2_add(vector2_t v1, vector2_t v2);
/// @brief Subtracts two 2D-vectors
vector2_t vector2_sub(vector2_t v1, vector2_t v2);
/// @brief returns the scalar product of two 2D-vectors
float vector2_sclpr(vector2_t v1, vector2_t v2);

#pragma endregion

#pragma region Vector3 operations

/// @brief Returns a length of 3D-vector
float vector3_length(vector3_t v);

/// @brief Sums two 3D-vectors
vector3_t vector3_add(vector3_t v1, vector3_t v2);
/// @brief Subtracts two 3D-vectors
vector3_t vector3_sub(vector3_t v1, vector3_t v2);
/// @brief returns the scalar product of two 3D-vectors
float vector3_sclpr(vector3_t v1, vector3_t v2);

/// @brief Rotating the vector by three axis
/// @param v a vector to be rotated
/// @param rotation the vector of angles in radians
/// @return The result of rotating `v` vector
vector3_t vector3_rotate(vector3_t v, vector3_t rotation);
/// @brief Rotating the vector by X
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vector3_t vector3_rotate_x(vector3_t v, float angle);
/// @brief Rotating the vector by Y
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vector3_t vector3_rotate_y(vector3_t v, float angle);
/// @brief Rotating the vector by Z
/// @param v a vector to be rotated
/// @param angle the angle of rotation in radians
/// @return The result of rotating `v` vector
vector3_t vector3_rotate_z(vector3_t v, float angle);

#pragma endregion

#endif