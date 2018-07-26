#include "polygon.h"
using namespace engine;

GraphicPolygon::GraphicPolygon() :
    GraphicPrimitive()
{

}

GraphicPolygon::~GraphicPolygon()
{

}

unsigned GraphicPolygon::GetVerticesCount() const
{
    return m_vertices.size();
}

const Vector2f& GraphicPolygon::GetVertex(unsigned index) const
{
    return m_vertices[index];
}

void GraphicPolygon::SetVerticesCount(unsigned count)
{
    m_vertices.resize(count);
}

void GraphicPolygon:: SetVertex(unsigned index, const Vector2f& vertex)
{
    m_vertices[index] = vertex;
}

void GraphicPolygon::Update(const float dt)
{

}

void GraphicPolygon::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    renderer.FillPolygon(m_vertices.data(), m_vertices.size(), m_backColor);
    if (m_borderStyle.IsVisible()) {
        renderer.DrawPolygon(m_vertices.data(), m_vertices.size(), m_borderStyle.GetColor(), m_borderStyle.GetThickness());
    }
}

