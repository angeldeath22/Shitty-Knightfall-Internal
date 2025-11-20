#pragma once
#include <cmath>
#include "Vector2.hpp"

struct Vector3 {
    float x, y, z;

    inline Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    inline Vector3(const Vector2& v, float z = 0.0f) : x(v.x), y(v.y), z(z) {}
    inline Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    inline Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    inline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    inline Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    inline Vector3 operator/(float s) const { return Vector3(x / s, y / s, z / s); }
    inline Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    inline Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    inline Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    inline Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
    inline bool operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
    inline bool operator!=(const Vector3& v) const { return !(*this == v); }

    inline float length() const { return std::sqrt(x * x + y * y + z * z); }
    inline float length_squared() const { return x * x + y * y + z * z; }
    inline Vector3 normalized() const {
        float len = length();
        return len != 0.0f ? Vector3(x / len, y / len, z / len) : Vector3(0.0f, 0.0f, 0.0f);
    }
    inline float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    inline Vector3 cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }


    inline static float Distance(const Vector3& a, const Vector3& b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        float dz = a.z - b.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};

inline Vector3 operator*(float s, const Vector3& v) { return v * s; }