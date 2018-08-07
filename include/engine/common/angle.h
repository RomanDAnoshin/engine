#ifndef ANGLE_H
#define ANGLE_H

#include "math.h"
#include "vector2.h"
#include <cmath>

namespace engine
{
    
struct Angle
{
    Angle(float radians = 0.f);

    static Angle FromRadians(float radians);

    static Angle FromDegrees(float degrees);

    static Angle FromVector(float x, float y);

    static Angle FromVector(const Vector2f& vector);

    float GetRadians() const;

    float GetDegrees() const;

    Vector2f GetVector() const;

    void SetRadians(float radians);

    void SetDegrees(float degrees);

    void SetVector(float x, float y);

    void SetVector(const Vector2f& vector);

    operator float() const;

private:
    float m_radians;
};
    
}

#endif // ANGLE_H
