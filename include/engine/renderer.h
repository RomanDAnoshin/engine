#ifndef RENDERER_H
#define RENDERER_H

#include "texture.h"
#include "transform.h"
#include "text/text.h"
#include <allegro5/allegro_primitives.h>

namespace engine
{

class Renderer
{
public:
    Renderer();

    const Transform& GetTransform();

    const Vector2f& GetScalingFactor() const;

    void SetTransform(const Transform& transform);

    void ResetTransform();

    const IntRect& GetClippingRectangle() const;

    void SetClippingRectangle(const IntRect& rect);

    void ResetClippingRectangle();

    void SetScalingFactor(const Vector2f& factor);

    void DrawBitmap(const Bitmap* bitmap, const IntRect& source, const FloatRect& dest) const;

    void DrawBitmap(const Bitmap* bitmap, const IntRect& source, const FloatRect& dest, const Color& color = Color()) const;

    void DrawText(const Font* font, const std::string& text, const Vector2f& position, HAlignment align, const Color& color) const;

    void DrawEllipse(const Vector2f& position, const Vector2f& size, const Color& color, float thickness = 0.f) const;

    void FillEllipse(const Vector2f& position, const Vector2f& size, const Color& color) const;

    void DrawRectangle(const Vector2f& position, const Vector2f& size, const Color& color, float thickness = 0.f) const;

    void FillRectangle(const Vector2f& position, const Vector2f& size, const Color& color) const;

    void DrawRoundedRectangle(const Vector2f& position, const Vector2f& size, const Color& color, float radius, float thickness = 0.f) const;

    void FillRoundedRectangle(const Vector2f& position, const Vector2f& size, const Color& color, float radius) const;

    void DrawPolygon(const Vector2f* points, unsigned count, const Color& color, float thickness = 0.f) const;

    void FillPolygon(const Vector2f* points, unsigned count, const Color& color) const;

protected:
    void useTransform();

    Transform   m_transform;
    IntRect     m_clip;
    Vector2f    m_factor;
};

}

#endif // RENDERER_H
