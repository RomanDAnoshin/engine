#ifndef VERTEX_H
#define VERTEX_H

#include "color.h"

namespace engine
{

struct Vertex
{
    Vertex();

    Vertex(float x, float y, float z, const Colorf& color = Colorf());

    float x, y, z;
    float u, v;
    Colorf color;
};

}

#endif // VERTEX_H
