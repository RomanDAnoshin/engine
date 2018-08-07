#ifndef RECT_H
#define RECT_H

#include "vector2.h"
#include "math.h"

namespace engine
{

template <typename T>
struct Rect
{
    Rect() :
        pos(Vector2<T>()),
        size(Vector2<T>())
    {

    }

    Rect(const Vector2<T>& pos, const Vector2<T>& size) :
        pos(pos),
        size(size)
    {

    }

    Rect(float x, float y, float width, float height) :
        pos(x, y),
        size(width, height)
    {

    }

    void Move(const Vector2<T>& distance)
    {
        pos += distance;
    }

    bool Intersects(const Rect& r) const
    {
        return ((pos.x + size.x > r.pos.x && pos.x < r.pos.x + r.size.x) &&
                (pos.y + size.y > r.pos.y && pos.y < r.pos.y + r.size.y));

    }

    Rect<T> GetIntersection(const Rect& r) const
    {
        if (!Intersects(r)) {
            return Rect<T>();
        }
        Rect<T> res;
        res.pos = Vector2<T>(math::max(pos.x, r.pos.x), math::max(pos.y, r.pos.y));
        res.size.x = math::min(pos.x + size.x, r.pos.x + r.size.x) - res.pos.x;
        res.size.y = math::min(pos.y + size.y, r.pos.y + r.size.y) - res.pos.y;
        return res;
    }

    bool operator==(const Rect<T>& r) const
    {
        const Rect& l = *this;
        return (l.pos == r.pos && l.size == r.size);
    }

    bool operator!=(const Rect<T>& r) const
    {
        const Rect& l = *this;
        return !(l == r);
    }

    Vector2<T> pos, size;
};


typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

}


#endif // RECT_H
