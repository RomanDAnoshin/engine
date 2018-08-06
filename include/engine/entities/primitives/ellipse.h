#ifndef GRAPHICELLIPSE_H
#define GRAPHICELLIPSE_H

#include "primitive.h"

namespace engine
{

class GraphicEllipse : public GraphicPrimitive
{
public:
    GraphicEllipse();

    const Vector2f& GetRadius() const;

    void SetRadius(float radius);

    void SetRadius(const Vector2f& radius);

    void Render(Renderer& renderer);

protected:
    Vector2f    m_radius;
};

}

#endif // GRAPHICELLIPSE_H
