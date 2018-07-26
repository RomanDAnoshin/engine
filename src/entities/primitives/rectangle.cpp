#include "entities/primitives/rectangle.h"
using namespace engine;

GraphicRectangle::GraphicRectangle() :
    GraphicPrimitive(),
    m_size(64.f, 64.f)
{

}

GraphicRectangle::~GraphicRectangle()
{

}

const Vector2f& GraphicRectangle::GetSize() const
{
    return m_size;
}

const Vector2f& GraphicRectangle::GetCenter() const
{
    return m_center;
}

void GraphicRectangle::SetSize(const Vector2f &size)
{
    m_size = size;
}

void GraphicRectangle::SetSize(float width, float height)
{
    Vector2f size(width, height);
    SetSize(size);
}

void GraphicRectangle::SetCenter(const Vector2f &center)
{
    m_center = center;
}

void GraphicRectangle::SetCenter(float x, float y)
{
    Vector2f center(x, y);
    SetCenter(center);
}

void GraphicRectangle::Update(const float dt)
{

}

void GraphicRectangle::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    renderer.FillRectangle(m_center * -1.f, m_size, m_backColor);
    if (m_borderStyle.IsVisible()) {
        renderer.DrawRectangle(m_center * -1.f, m_size, m_borderStyle.GetColor(), m_borderStyle.GetThickness());
    }
}

Event<const Vector2f&>& GraphicRectangle::EventSizeChanged()
{
    return m_sizeChanged;
}

GraphicRoundedRectangle::GraphicRoundedRectangle() :
    m_radius(5.f)
{

}

GraphicRoundedRectangle::~GraphicRoundedRectangle()
{

}

float GraphicRoundedRectangle::GetRadius() const
{
    return m_radius;
}

void GraphicRoundedRectangle::SetRadius(float radius)
{
    m_radius = radius;
}

void GraphicRoundedRectangle::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    renderer.FillRoundedRectangle(m_center * -1.f, m_size, m_backColor, m_radius);
    if (m_borderStyle.IsVisible()) {
        renderer.DrawRoundedRectangle(m_center * -1.f, m_size, m_borderStyle.GetColor(), m_radius, m_borderStyle.GetThickness());
    }
}
