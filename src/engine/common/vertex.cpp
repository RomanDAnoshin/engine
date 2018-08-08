#include "engine/common/vertex.h"
using namespace engine;

Vertex::Vertex() :
    Vertex(0.f, 0.f, 0.f)
{

}

Vertex::Vertex(float x, float y, float z, const Colorf& color) :
    x(x),
    y(y),
    z(z),
    u(0.f),
    v(0.f),
    color(color)
{

}
