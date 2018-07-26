#include "entities/primitives/primitives.h"
using namespace engine;

BorderStyle::BorderStyle() :
    m_color(Color(0, 0, 0)),
    m_thickness(0.f),
    m_visible(false)
{

}

BorderStyle::BorderStyle(const Color& color, float thickness) :
    m_color(color),
    m_thickness(thickness),
    m_visible(true)
{

}

const Color& BorderStyle::GetColor() const
{
    return m_color;
}

float BorderStyle::GetThickness() const
{
    return m_thickness;
}

bool BorderStyle::IsVisible() const
{
    return m_visible;
}

void BorderStyle::SetColor(const Color& color)
{
    m_color = color;
}

void BorderStyle::SetThickness(float thickness)
{
    m_thickness = thickness;
}

void BorderStyle::SetVisible(bool visible)
{
    m_visible = visible;
}

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

BorderStyle&GraphicPrimitive::GetBorderStyle()
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
