#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "engine/entities/entity.h"
#include "engine/common/borderstyle.h"

namespace engine
{

class GraphicPrimitive : public Entity
{
public:
    GraphicPrimitive();

    virtual ~GraphicPrimitive() = 0;

    const Color& GetColor() const;

    const BorderStyle& GetBorderStyle();

    void SetColor(const Color& color);

    void SetBorderStyle(const BorderStyle& borderStyle);

protected:
    Color       m_color;
    BorderStyle m_borderStyle;
};

}

#endif // PRIMITIVE_H
