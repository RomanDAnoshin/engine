#ifndef GRAPHICPOLYGON_H
#define GRAPHICPOLYGON_H

#include "primitive.h"
#include <vector>

namespace engine
{

class GraphicPolygon : public GraphicPrimitive
{
public:
    GraphicPolygon();

    virtual ~GraphicPolygon();

    unsigned GetVerticesCount() const;

    const Vector2f& GetVertex(unsigned index) const;

    void SetVerticesCount(unsigned count);

    void SetVertex(unsigned index, const Vector2f& vertex);

    void SetVertices(std::initializer_list<Vector2f> vertices);

    virtual void Render(Renderer& renderer);

protected:
    std::vector<Vector2f>   m_vertices;
    Vector2f                m_scale;
};

}

#endif // GRAPHICPOLYGON_H
