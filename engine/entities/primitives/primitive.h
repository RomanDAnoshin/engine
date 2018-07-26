#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "entities/entity.h"

namespace engine
{

class BorderStyle
{
public:
    BorderStyle();

    BorderStyle(const Color& color, float thickness = 0.f);

    const Color& GetColor() const;

    float GetThickness() const;

    bool IsVisible() const;

    void SetColor(const Color& color);

    void SetThickness(float thickness);

    void SetVisible(bool visible);

private:
    Color   m_color;
    float   m_thickness;
    float   m_radius;
    bool    m_visible;
};

class GraphicPrimitive : public Entity
{
public:
    GraphicPrimitive();

    virtual ~GraphicPrimitive() = 0;

    const Color& GetBackColor() const;

    BorderStyle& GetBorderStyle();

    void SetBackColor(const Color& backColor);

    void SetBorderStyle(const BorderStyle& borderStyle);

protected:
    Color       m_backColor;
    BorderStyle m_borderStyle;
};

}

#endif // PRIMITIVE_H
