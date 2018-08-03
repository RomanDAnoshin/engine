#ifndef GRAPHICRECTANGLE_H
#define GRAPHICRECTANGLE_H

#include "primitive.h"

namespace engine
{

class GraphicRectangle : public GraphicPrimitive
{
public:
    GraphicRectangle();

    virtual ~GraphicRectangle();

    const Vector2f& GetSize() const;

    const Vector2f& GetCenter() const;

    void SetSize(const Vector2f& size);

    void SetSize(float width, float height);

    void SetCenter(const Vector2f& center);

    void SetCenter(float x, float y);

    virtual void Render(Renderer& renderer);

    Event<const Vector2f&>& EventSizeChanged();

protected:
    Vector2f    m_size;
    Vector2f    m_center;

private:
    Event<const Vector2f&> m_sizeChanged;
};

class GraphicRoundedRectangle : public GraphicRectangle
{
public:
    GraphicRoundedRectangle();

    virtual ~GraphicRoundedRectangle();

    float GetRadius() const;

    void SetRadius(float radius);

    virtual void Render(Renderer &renderer);

protected:
    float   m_radius;
};

}

#endif // GRAPHICRECTANGLE_H
