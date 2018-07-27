#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "engine/entities/entity.h"

namespace engine
{

class GraphicPrimitive : public Entity
{
public:
    GraphicPrimitive();

    virtual ~GraphicPrimitive() = 0;

    const Color& GetBackColor() const;

    const BorderStyle& GetBorderStyle();

    void SetBackColor(const Color& backColor);

    void SetBorderStyle(const BorderStyle& borderStyle);

protected:
    Color       m_backColor;
    BorderStyle m_borderStyle;
};

}

#endif // PRIMITIVE_H
