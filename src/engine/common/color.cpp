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

ColorF::ColorF() :
    BaseColor<float>(1.f, 1.f, 1.f, 1.f)
{

}

ColorF::ColorF(float r, float g, float b, float a) :
    BaseColor<float>(r, g, b, a)
{

}

ColorF::ColorF(const ColorF& color) :
    ColorF(color.r, color.g, color.b, color.a)
{

}

ColorF::ColorF(const BaseColor<float>& base) :
    BaseColor<float>(base)
{

}
