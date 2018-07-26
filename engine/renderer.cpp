#include "renderer.h"
using namespace engine;

Renderer::Renderer() :
    m_factor(1.f, 1.f)
{

}

const Transform& Renderer::GetTransform()
{
    return m_transform;
}

const Vector2f&Renderer::GetScalingFactor() const
{
    return m_factor;
}

void Renderer::SetTransform(const Transform& transform)
{
    m_transform = transform;
    useTransform();
}

void Renderer::ResetTransform()
{
    m_transform.Reset();
    useTransform();
}

const IntRect& Renderer::GetClippingRectangle() const
{
    return m_clip;
}

void Renderer::SetClippingRectangle(const IntRect& rect)
{
    m_clip = rect;
    al_set_clipping_rectangle(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y);
}

void Renderer::ResetClippingRectangle()
{
    al_reset_clipping_rectangle();
    al_get_clipping_rectangle(&m_clip.pos.x, &m_clip.pos.y, &m_clip.size.x, &m_clip.size.y);
}

void Renderer::SetScalingFactor(const Vector2f& factor)
{
    m_factor = factor;
    useTransform();
}

void Renderer::DrawBitmap(const Bitmap* bitmap, const IntRect& source, const FloatRect& dest, const Color& color) const
{
    if (color == Color()) {
        al_draw_scaled_bitmap(bitmap->m_bitmap,
                              source.pos.x, source.pos.y, source.size.x, source.size.y,
                              dest.pos.x, dest.pos.y, dest.size.x, dest.size.y, 0);
    }
    else {
        al_draw_tinted_scaled_bitmap(bitmap->m_bitmap,
                                     al_map_rgba(color.r, color.g, color.b, color.a),
                                     source.pos.x, source.pos.y, source.size.x, source.size.y,
                                     dest.pos.x, dest.pos.y, dest.size.x, dest.size.y, 0);
    }
}

void Renderer::DrawText(const Font* font, const std::string& text, const Vector2f& position, HAlignment align, const Color& color) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_text(font->m_font, c, position.x, position.y, static_cast<int>(align), text.c_str());
}

void Renderer::DrawEllipse(const Vector2f& position, const Vector2f& size, const Color& color, float thickness) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_ellipse(position.x, position.y, size.x, size.y, c, thickness);
}

void Renderer::FillEllipse(const Vector2f& position, const Vector2f& size, const Color& color) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_filled_ellipse(position.x, position.y, size.x, size.y, c);
}

void Renderer::DrawRectangle(const Vector2f& position, const Vector2f& size, const Color& color, float thickness) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_rectangle(position.x, position.y, position.x + size.x, position.y + size.y, c, thickness);
}

void Renderer::FillRectangle(const Vector2f& position, const Vector2f& size, const Color& color) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_filled_rectangle(position.x, position.y, position.x + size.x, position.y + size.y, c);
}

void Renderer::DrawRoundedRectangle(const Vector2f& position, const Vector2f& size, const Color& color, float radius, float thickness) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_rounded_rectangle(position.x, position.y, position.x + size.x, position.y + size.y, radius, radius, c, thickness);
}

void Renderer::FillRoundedRectangle(const Vector2f& position, const Vector2f& size, const Color& color, float radius) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    al_draw_filled_rounded_rectangle(position.x, position.y, position.x + size.x, position.y + size.y, radius, radius, c);
}

void Renderer::DrawPolygon(const Vector2f* points, unsigned count, const Color& color, float thickness) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    const float* data = reinterpret_cast<const float*>(points);
    al_draw_polygon(data, count, ALLEGRO_LINE_JOIN_NONE, c, thickness, 0.f);
}

void Renderer::FillPolygon(const Vector2f* points, unsigned count, const Color& color) const
{
    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);
    const float* data = reinterpret_cast<const float*>(points);
    al_draw_filled_polygon(data, count, c);
}

void Renderer::useTransform()
{
    Transform transform = m_transform;
    transform.Scale(m_factor);
    const ALLEGRO_TRANSFORM* tr = reinterpret_cast<const ALLEGRO_TRANSFORM*>(&transform);
    al_use_transform(tr);
}
