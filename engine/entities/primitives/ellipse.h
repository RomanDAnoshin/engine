#ifndef GRAPHICELLIPSE_H
#define GRAPHICELLIPSE_H

#include "primitive.h"

namespace engine
{

class GraphicEllipse : public GraphicPrimitive
{
public:
    GraphicEllipse();

    virtual ~GraphicEllipse();

    const Vector2f& GetRadius() const;

    void SetRadius(float radius);

    void SetRadius(const Vector2f& radius);

    virtual void Update(const float dt);

    virtual void Render(Renderer& renderer);

protected:
    Vector2f    m_radius;
};

}

#endif // GRAPHICELLIPSE_H
