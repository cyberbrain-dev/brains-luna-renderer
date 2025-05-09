#include "vector.h"

#include <cmath>

namespace luna
{
    float Vector2::magnitude() const noexcept
    {
        return std::sqrt((x * x) + (y * y));
    }

    void Vector2::normalize() noexcept
    {
        float m = magnitude();
        if (m != 0.0f)
        {
            x /= m;
            y /= m;
        }
    }

    float Vector2::dot(const Vector2& v1, const Vector2& v2) noexcept
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    float Vector3::magnitude() const noexcept
    {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    void Vector3::normalize() noexcept
    {
        float m = magnitude();
        if (m != 0.0f)
        {
            x /= m;
            y /= m;
            z /= m;
        }
    }

    float Vector3::dot(const Vector3& v1, const Vector3& v2) noexcept
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }

    Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) noexcept
    {
        Vector3 result = 
        {
            (v1.y * v2.z) - (v1.z * v2.y),
            (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)
        };

        return result;
    }

    Vector3 Vector3::rotate(const Vector3& rotation) const noexcept
    {
        Vector3 rotated_vector = rotate_x(rotation.x);
        rotated_vector = rotated_vector.rotate_y(rotation.y);
        rotated_vector = rotated_vector.rotate_z(rotation.z);

        return rotated_vector;
    }

    Vector3 Vector3::rotate_x(float angle) const noexcept
    {
        Vector3 rotated_vector = {
            x,
            y * std::cos(angle) - z * std::sin(angle),
            y * std::sin(angle) + z * std::cos(angle)
        };
    
        return rotated_vector;
    }

    Vector3 Vector3::rotate_y(float angle) const noexcept
    {
        Vector3 rotated_vector = {
            x * std::cos(angle) - z * std::sin(angle),
            y,
            x * std::sin(angle) + z * std::cos(angle)
        };
    
        return rotated_vector;
    }

    Vector3 Vector3::rotate_z(float angle) const noexcept
    {
        Vector3 rotated_vector = {
            x * std::cos(angle) - y * std::sin(angle),
            x * std::sin(angle) + y * std::cos(angle),
            z
        };
        
        return rotated_vector;
    }
}