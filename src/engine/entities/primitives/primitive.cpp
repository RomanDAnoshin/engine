#include "engine/entities/primitives/primitives.h"
using namespace engine;

GraphicPrimitive::GraphicPrimitive() :
    Entity()
{

}

GraphicPrimitive::~GraphicPrimitive()
{

}

const Color& GraphicPrimitive::GetBackColor() const
{
    return m_backColor;
}

const engine::BorderStyle& GraphicPrimitive::GetBorderStyle()
{
    return m_borderStyle;
}

void GraphicPrimitive::SetBackColor(const Color &backColor)
{
    m_backColor = backColor;
}

void GraphicPrimitive::SetBorderStyle(const BorderStyle& borderStyle)
{
    m_borderStyle = borderStyle;
}
