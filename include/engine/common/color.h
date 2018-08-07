#ifndef COLOR_H
#define COLOR_H

namespace engine
{

template <typename T>
struct BaseColor
{
    BaseColor(T r, T g, T b, T a) :
        r(r),
        g(g),
        b(b),
        a(a)
    {

    }

    BaseColor(const BaseColor<T>& color) :
        r(color.r),
        g(color.g),
        b(color.b),
        a(color.a)
    {

    }

    BaseColor<T> operator+(const BaseColor<T>& r) const
    {
        const BaseColor& l = *this;
        return BaseColor<T>(l.r + r.r, l.g + r.g, l.b + r.b, l.a + r.a);
    }

    BaseColor<T> operator-(const BaseColor<T>& r) const
    {
        const BaseColor& l = *this;
        return BaseColor<T>(l.r - r.r, l.g - r.g, l.b - r.b, l.a + r.a);
    }

    BaseColor<T> operator*(float r) const
    {
        const BaseColor& l = *this;
        return BaseColor<T>(l.r * r, l.g * r, l.b * r, l.a * r);
    }

    BaseColor<T> operator/(float r) const
    {
        const BaseColor& l = *this;
        return BaseColor<T>(l.r / r, l.g / r, l.b / r, l.a / r);
    }

    BaseColor<T> operator+=(const BaseColor<T>& r)
    {
        BaseColor& l = *this;
        return l = l + r;
    }

    BaseColor<T> operator-=(const BaseColor<T>& r)
    {
        BaseColor& l = *this;
        return l = l - r;
    }

    BaseColor<T> operator*=(float r)
    {
        BaseColor& l = *this;
        return l = l * r;
    }

    BaseColor<T> operator/=(float r)
    {
        BaseColor& l = *this;
        return l = l / r;
    }

    bool operator==(const BaseColor<T>& r) const
    {
        const BaseColor& l = *this;
        return (l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a);
    }

    bool operator!=(const BaseColor<T>& r) const
    {
        const BaseColor& l = *this;
        return !(l == r);
    }

    T r, g, b, a;
};

struct Color : BaseColor<unsigned char>
{
    Color();

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

    Color(const Color& color);

    Color(const BaseColor<unsigned char>& base);
};


struct ColorF : BaseColor<float>
{
    ColorF();

    ColorF(float r, float g, float b, float a = 1.f);

    ColorF(const ColorF& color);

    ColorF(const BaseColor<float>& base);
};

}

#endif // COLOR_H
