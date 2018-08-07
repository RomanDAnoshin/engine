#include "engine/entities/primitives/primitives.h"
using namespace engine;

GraphicPrimitive::GraphicPrimitive() :
    Entity()
{

}

GraphicPrimitive::~GraphicPrimitive() = default;

const Color& GraphicPrimitive::GetColor() const
{
    return m_color;
}

const engine::BorderStyle& GraphicPrimitive::GetBorderStyle()
{
    return m_borderStyle;
}

void GraphicPrimitive::SetColor(const Color& color)
{
    m_color = color;
}

void GraphicPrimitive::SetBorderStyle(const BorderStyle& borderStyle)
{
    m_borderStyle = borderStyle;
}
