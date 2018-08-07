#include "engine/common/borderstyle.h"
using namespace engine;

BorderStyle::BorderStyle() :
    color(0, 0, 0),
    thickness(0.f),
    visible(false)
{

}

BorderStyle::BorderStyle(const Color& color, float thickness) :
    color(color),
    thickness(thickness),
    visible(true)
{

}
