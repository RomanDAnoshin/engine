#include "engine/common/angle.h"
using namespace engine;

Angle::Angle(float radians) :
    m_radians(radians)
{
    
}

Angle Angle::FromRadians(float radians)
{
    Angle angle;
    angle.SetRadians(radians);
    return angle;
}

Angle Angle::FromDegrees(float degrees)
{
    Angle angle;
    angle.SetDegrees(degrees);
    return angle;
}

Angle Angle::FromVector(float x, float y)
{
    Angle angle;
    angle.SetVector(x, y);
    return angle;
}

Angle Angle::FromVector(const Vector2f& vector)
{
    return FromVector(vector.x, vector.y);
}

float Angle::GetRadians() const
{
    return m_radians;
}

float Angle::GetDegrees() const
{
    return math::toDegrees(m_radians);
}

Vector2f Angle::GetVector() const
{
    return Vector2f(std::cos(m_radians), std::sin(m_radians));
}

void Angle::SetRadians(float radians)
{
    m_radians = radians;
}

void Angle::SetDegrees(float degrees)
{
    m_radians = math::toRadians(degrees);
}

void Angle::SetVector(float x, float y)
{
    m_radians = std::atan2(y, x);
}

void Angle::SetVector(const Vector2f& vector)
{
    SetVector(vector.x, vector.y);
}

Angle::operator float() const
{
    return m_radians;
}
