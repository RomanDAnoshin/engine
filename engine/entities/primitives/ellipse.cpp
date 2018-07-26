#include "ellipse.h"
using namespace engine;

GraphicEllipse::GraphicEllipse() :
    GraphicPrimitive(),
    m_radius(32.f, 32.f)
{

}

GraphicEllipse::~GraphicEllipse()
{

}

const Vector2f& GraphicEllipse::GetRadius() const
{
    return m_radius;
}

void GraphicEllipse::SetRadius(float radius)
{
    m_radius = Vector2f(radius, radius);
}

void GraphicEllipse::SetRadius(const Vector2f &radius)
{
    m_radius = radius;
}

void GraphicEllipse::Update(const float dt)
{

}

void GraphicEllipse::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    renderer.FillEllipse(Vector2f(0.f, 0.f), m_radius, m_backColor);
    if (m_borderStyle.IsVisible()) {
        renderer.DrawEllipse(Vector2f(0.f, 0.f), m_radius, m_borderStyle.GetColor(), m_borderStyle.GetThickness());
    }
}
