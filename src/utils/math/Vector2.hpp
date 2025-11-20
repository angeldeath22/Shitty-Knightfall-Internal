#pragma once
#include <cmath>

struct Vector2 {
    float x, y;

    inline Vector2() : x(0.0f), y(0.0f) {}
    inline Vector2(float x, float y) : x(x), y(y) {}
    inline Vector2(const Vector2& v) : x(v.x), y(v.y) {}

    inline Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    inline Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    inline Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
    inline Vector2 operator/(float s) const { return Vector2(x / s, y / s); }
    inline Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    inline Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    inline Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
    inline Vector2& operator/=(float s) { x /= s; y /= s; return *this; }
    inline bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
    inline bool operator!=(const Vector2& v) const { return !(*this == v); }

    inline float length() const { return std::sqrt(x * x + y * y); }
    inline float length_squared() const { return x * x + y * y; }
    inline Vector2 normalized() const {
        float len = length();
        return len != 0.0f ? Vector2(x / len, y / len) : Vector2(0.0f, 0.0f);
    }
    inline float dot(const Vector2& v) const { return x * v.x + y * v.y; }
    inline float cross(const Vector2& v) const { return x * v.y - y * v.x; }
};

inline Vector2 operator*(float s, const Vector2& v) { return v * s; }