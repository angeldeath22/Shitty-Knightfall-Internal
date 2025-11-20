#pragma once
#include <cmath>

struct Quaternion {
    float x, y, z, w;

    inline Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    inline Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    inline Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

    inline Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w,
            w * q.w - x * q.x - y * q.y - z * q.z
        );
    }

    inline Quaternion& operator*=(const Quaternion& q) {
        *this = *this * q;
        return *this;
    }

    inline float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }
    inline Quaternion normalized() const {
        float len = length();
        return len != 0.0f ? Quaternion(x / len, y / len, z / len, w / len) : Quaternion(0, 0, 0, 1);
    }

    inline Quaternion conjugate() const { return Quaternion(-x, -y, -z, w); }
    inline Quaternion inverse() const { return conjugate() / (x * x + y * y + z * z + w * w); }

    inline Quaternion operator/(float s) const { return Quaternion(x / s, y / s, z / s, w / s); }
    inline Quaternion& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
};