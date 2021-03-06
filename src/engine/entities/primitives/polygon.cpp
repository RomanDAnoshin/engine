#include "engine/entities/primitives/polygon.h"
using namespace engine;

GraphicPolygon::GraphicPolygon() :
    GraphicPrimitive()
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

void GraphicPolygon::SetVertices(std::initializer_list<Vector2f> vertices)
{
    m_vertices = std::vector<Vector2f>(vertices);
}

void GraphicPolygon::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    renderer.FillPolygon(m_vertices.data(), m_vertices.size(), m_color);
    if (m_borderStyle.visible) {
        renderer.DrawPolygon(m_vertices.data(), m_vertices.size(), m_borderStyle.color, m_borderStyle.thickness);
    }
}

