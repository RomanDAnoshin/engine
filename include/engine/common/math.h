#ifndef MATH_H
#define MATH_H

namespace engine
{
namespace math
{

static const float pi = 3.14159265359f;

float toRadians(float degrees);

float toDegrees(float radians);

template <typename T>
const T& min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template <typename T>
const T& max(const T& a, const T& b)
{
    return a > b ? a : b;
}

template <typename T>
const T& clamp(const T& value, const T& lower, const T& upper)
{
    return math::min(upper, math::max(value, lower));
}

template <typename T>
T lerp(const T& a, const T& b, float ratio) {
    return a + T(b - a) * ratio;
}

}
}

#endif // MATH_H
