#include "engine/common/color.h"
using namespace engine;

Color::Color() :
    BaseColor<unsigned char>(255, 255, 255, 255)
{

}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
    BaseColor<unsigned char>(r, g, b, a)
{

}

Color::Color(const Color& color) :
    Color(color.r, color.g, color.b, color.a)
{

}

Color::Color(const BaseColor<unsigned char>& base) :
    BaseColor<unsigned char>(base)
{

}

engine::Color::operator Colorf() const
{
    return Colorf(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

Colorf::Colorf() :
    BaseColor<float>(1.f, 1.f, 1.f, 1.f)
{

}

Colorf::Colorf(float r, float g, float b, float a) :
    BaseColor<float>(r, g, b, a)
{

}

Colorf::Colorf(const Colorf& color) :
    Colorf(color.r, color.g, color.b, color.a)
{

}

Colorf::Colorf(const BaseColor<float>& base) :
    BaseColor<float>(base)
{

}

Colorf::operator Color() const
{
    return Color(static_cast<unsigned char>(r * 255),
                 static_cast<unsigned char>(g * 255),
                 static_cast<unsigned char>(b * 255),
                 static_cast<unsigned char>(a * 255));

}
