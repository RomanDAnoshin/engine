#ifndef BORDERSTYLE_H
#define BORDERSTYLE_H

#include "color.h"

namespace engine
{

struct BorderStyle
{
    BorderStyle();

    BorderStyle(const Color& color, float thickness = 0.f);

    Color   color;
    float   thickness;
    bool    visible;
};

}

#endif // BORDERSTYLE_H
