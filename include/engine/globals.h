#ifndef GLOBALS_H
#define GLOBALS_H

#include <algorithm>

namespace engine
{

template <typename T>
struct Vector2
{
    Vector2() : x(T()), y(T()) { }
    Vector2(const T& x, const T& y) : x(x), y(y) { }

    void Sort() {
        if (x > y) {
            T t = x;
            x = y;
            y = t;
        }
    }

    template <typename U>
    operator Vector2<U>() const {
        return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
    }

    T x, y;
};

template <typename T>
Vector2<T> operator+(const Vector2<T>& l, const Vector2<T>& r) { return Vector2<T>(l.x + r.x, l.y + r.y); }

template <typename T>
Vector2<T> operator-(const Vector2<T>& l, const Vector2<T>& r) { return Vector2<T>(l.x - r.x, l.y - r.y); }

template <typename T>
Vector2<T> operator*(const Vector2<T>& l, float r) { return Vector2<T>(l.x * r, l.y * r); }

template <typename T>
Vector2<T> operator/(const Vector2<T>& l, float r) { return Vector2<T>(l.x / r, l.y / r); }

template <typename T>
Vector2<T> operator+=(Vector2<T>& l, const Vector2<T>& r) {
    l.x += r.x;
    l.y += r.y;
    return l;
}

template <typename T>
Vector2<T> operator-=(Vector2<T>& l, const Vector2<T>& r) {
    l.x -= r.x;
    l.y -= r.y;
    return l;
}

template <typename T>
Vector2<T> operator*=(Vector2<T>& l, float r) {
    l.x *= r;
    l.y *= r;
    return l;
}

template <typename T>
Vector2<T> operator/=(Vector2<T>& l, float r) {
    l.x /= r;
    l.y /= r;
    return l;
}

template <typename T>
bool operator==(const Vector2<T>& l, const Vector2<T>& r) {
    return (l.x == r.x && l.y == r.y);
}

template <typename T>
bool operator!=(const Vector2<T>& l, const Vector2<T>& r) {
    return !(l == r);
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned> Vector2u;

template <typename T>
struct Rect
{
    Rect() : pos(Vector2<T>()), size(Vector2<T>()) { }
    Rect(const Vector2<T>& pos, const Vector2<T>& size) : pos(pos), size(size) { }
    Rect(float x, float y, float width, float height) : pos(x, y), size(width, height) { }

    void Move(const Vector2<T>& distance) { pos += distance; }

    bool Intersects(const Rect& r) const {
        return ((pos.x + size.x > r.pos.x && pos.x < r.pos.x + r.size.x) &&
                (pos.y + size.y > r.pos.y && pos.y < r.pos.y + r.size.y));

    }

    Rect<T> Intersection(const Rect& r) const {
        if (!Intersects(r))
            return Rect<T>();
        Rect<T> res;
        res.pos = Vector2<T>(std::max(pos.x, r.pos.x), std::max(pos.y, r.pos.y));
        res.size.x = std::min(pos.x + size.x, r.pos.x + r.size.x) - res.pos.x;
        res.size.y = std::min(pos.y + size.y, r.pos.y + r.size.y) - res.pos.y;
        return res;
    }

    Vector2<T> pos, size;
};

template <typename T>
bool operator==(const Rect<T>& l, const Rect<T>& r) {
    return (l.pos == r.pos && l.size == r.size);
}

template <typename T>
bool operator!=(const Rect<T>& l, const Rect<T>& r) {
    return !(l == r);
}

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

struct Color
{
    Color() : r(255), g(255), b(255), a(255) { }

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) :
        r(r), g(g), b(b), a(a) { }

    unsigned char r, g, b, a;
};

inline Color operator+(const Color& l, const Color& r) { return Color(l.r + r.r, l.g + r.g, l.b + r.b, l.a + r.a); }

inline Color operator-(const Color& l, const Color& r) { return Color(l.r - r.r, l.g - r.g, l.b - r.b, l.a + r.a); }

inline Color operator*(const Color& l, float r) { return Color(l.r * r, l.g * r, l.b * r, l.a * r); }

inline Color operator/(const Color& l, float r) { return Color(l.r / r, l.g / r, l.b / r, l.a / r); }

inline Color operator+=(Color& l, const Color& r) {
    l.r += r.r;
    l.g += r.g;
    l.b += r.b;
    l.a += r.a;
    return l;
}

inline Color operator-=(Color& l, const Color& r) {
    l.r -= r.r;
    l.g -= r.g;
    l.b -= r.b;
    l.a -= r.a;
    return l;
}

inline Color operator*=(Color& l, float r) {
    l.r *= r;
    l.g *= r;
    l.b *= r;
    l.a *= r;
    return l;
}

inline Color operator/=(Color& l, float r) {
    l.r /= r;
    l.g /= r;
    l.b /= r;
    l.a /= r;
    return l;
}

inline bool operator==(const Color& l, const Color& r) {
    return (l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a);
}

inline bool operator!=(const Color& l, const Color& r) {
    return !(l == r);
}

inline float degreesToRadians(float degrees) {
    return degrees * 0.0174532925f;
}

inline float radiansToDegrees(float radians) {
    return radians * 57.2957795f;
}


struct BorderStyle
{
    BorderStyle() :
        color(0, 0, 0), thickness(0.f), visible(false) { }
    BorderStyle(const Color& color, float thickness = 0.f) :
        color(color), thickness(thickness), visible(true) { }

    Color color;
    float thickness;
    bool visible;
};

}

#endif // GLOBALS_H
