#pragma once
#include <cmath>
#include "Vector3.hpp"

struct Vector4 {
    float x, y, z, w;

    inline Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    inline Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    inline Vector4(const Vector3& v, float w = 0.0f) : x(v.x), y(v.y), z(v.z), w(w) {}
    inline Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    inline Vector4 operator+(const Vector4& v) const { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
    inline Vector4 operator-(const Vector4& v) const { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
    inline Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
    inline Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }
    inline Vector4& operator+=(const Vector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
    inline Vector4& operator-=(const Vector4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
    inline Vector4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
    inline Vector4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
    inline bool operator==(const Vector4& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
    inline bool operator!=(const Vector4& v) const { return !(*this == v); }

    inline float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }
    inline float length_squared() const { return x * x + y * y + z * z + w * w; }
    inline Vector4 normalized() const {
        float len = length();
        return len != 0.0f ? Vector4(x / len, y / len, z / len, w / len) : Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    inline float dot(const Vector4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
};

inline Vector4 operator*(float s, const Vector4& v) { return v * s; }