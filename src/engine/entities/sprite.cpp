#include "engine/entities/sprite.h"
using namespace engine;

Sprite::Sprite(const Bitmap* bitmap) :
    GraphicRectangle(),
    Textured(bitmap)
{
    m_size = bitmap == nullptr ? Vector2f(0.f, 0.f) : Vector2f(bitmap->GetSize());
}

void Sprite::Render(Renderer& renderer)
{
    if (m_bitmap != nullptr) {
        prepareRenderer(renderer);
        renderer.DrawBitmap(m_bitmap, m_source, FloatRect(m_center * -1.f, m_size), m_color);
    }
}
