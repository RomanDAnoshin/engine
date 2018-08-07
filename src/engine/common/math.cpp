#include "engine/common/math.h"
using namespace engine;

float math::toRadians(float degrees)
{
    return degrees * 0.0174532925f;
}

float math::toDegrees(float radians)
{
    return radians * 57.2957795f;
}
