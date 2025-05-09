#pragma once

namespace luna
{
    /// @brief Represents a vector in a two-dimensional space
    struct Vector2
    {
        float x{};
        float y{};


        /// @brief Creates a zero 2D-vector
        Vector2() noexcept = default;
        /// @brief Creates a 2D-vector
        Vector2(float x, float y) noexcept : x{x}, y{y} {}
    

        Vector2 operator +(const Vector2& other) const noexcept
        {
            return Vector2(x + other.x, y + other.y);
        }
        Vector2 operator -(const Vector2& other) const noexcept
        {
            return Vector2(x - other.x, y - other.y);
        }
        Vector2 operator *(float scalar) const noexcept
        {
            return Vector2(x * scalar, y * scalar);
        }
        Vector2 operator /(float scalar) const noexcept
        {
            return Vector2(x / scalar, y / scalar);
        }

        /// @brief Returns a length of 2D-vector
        float magnitude() const noexcept;

        /// @brief Normalizes the vector
        void normalize() noexcept;

        /// @brief Returns the dot product of two 2D-vectors
        static float dot(const Vector2& v1, const Vector2& v2) noexcept;
    };

    /// @brief Represents a vector in a three-dimensional space
    struct Vector3
    {
        float x{};
        float y{};
        float z{};


        /// @brief Creates a zero 3D-vector
        Vector3() noexcept = default;
        /// @brief Creates a 3D-vector
        Vector3(float x, float y, float z) noexcept : x{x}, y{y}, z{z} {}
    

        Vector3 operator +(const Vector3& other) const noexcept
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        Vector3 operator -(const Vector3& other) const noexcept
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        Vector3 operator *(float scalar) const noexcept
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        Vector3 operator /(float scalar) const noexcept
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        /// @brief Returns a length of 3D-vector
        float magnitude() const noexcept;

        /// @brief Normalizes the vector
        void normalize() noexcept;

        /// @brief Returns the dot product of two 3D-vectors
        static float dot(const Vector3& v1, const Vector3& v2) noexcept;
        /// @brief Returns a cross product of two 3D-vectors
        static Vector3 cross(const Vector3& v1, const Vector3& v2) noexcept;

        /// @brief Returns a new vector, 
        /// which is the result of rotation of the vector
        /// @param rotation A vector with angles in radians
        Vector3 rotate(const Vector3& rotation) const noexcept;

    private:
        Vector3 rotate_x(float angle) const noexcept;
        Vector3 rotate_y(float angle) const noexcept;
        Vector3 rotate_z(float angle) const noexcept;
    };
}