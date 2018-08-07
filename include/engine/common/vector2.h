#ifndef VECTOR2_H
#define VECTOR2_H

namespace engine
{

template <typename T>
struct Vector2
{
    Vector2() :
        x(T()),
        y(T())
    {

    }

    Vector2(const T& x, const T& y) :
        x(x),
        y(y)
    {

    }

    Vector2(const T& value) :
        x(value),
        y(value)
    {

    }

    void Sort()
    {
        if (x > y) {
            T t = x;
            x = y;
            y = t;
        }
    }

    template <typename U>
    operator Vector2<U>() const
    {
        return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
    }

    Vector2<T> operator+(const Vector2<T>& r) const
    {
        const Vector2& l = *this;
        return Vector2<T>(l.x + r.x, l.y + r.y);
    }

    Vector2<T> operator-(const Vector2<T>& r) const
    {
        const Vector2& l = *this;
        return Vector2<T>(l.x - r.x, l.y - r.y);
    }

    Vector2<T> operator*(float r) const
    {
        const Vector2& l = *this;
        return Vector2<T>(l.x * r, l.y * r);
    }

    Vector2<T> operator/(float r) const
    {
        const Vector2& l = *this;
        return Vector2<T>(l.x / r, l.y / r);
    }

    Vector2<T> operator+=(const Vector2<T>& r)
    {
        Vector2& l = *this;
        return l = l + r;
    }

    Vector2<T> operator-=(const Vector2<T>& r)
    {
        Vector2& l = *this;
        return l = l - r;
    }

    Vector2<T> operator*=(float r)
    {
        Vector2& l = *this;
        return l = l * r;
    }

    Vector2<T> operator/=(float r)
    {
        Vector2& l = *this;
        return l = l / r;
    }

    bool operator==(const Vector2<T>& r) const
    {
        const Vector2& l = *this;
        return (l.x == r.x && l.y == r.y);
    }

    bool operator!=(const Vector2<T>& r) const
    {
        const Vector2& l = *this;
        return !(l == r);
    }

    T x, y;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned> Vector2u;

}

#endif // VECTOR2_H
