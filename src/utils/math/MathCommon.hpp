#pragma once
#include <cmath>

static inline float to_radians(float degrees) { return degrees * 3.14159265359f / 180.0f;}
static inline float to_degrees(float radians) { return radians * 180.0f / 3.14159265359f;}