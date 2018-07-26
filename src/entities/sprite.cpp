#include "entities/sprite.h"
using namespace engine;

Sprite::Sprite(const Bitmap* bitmap) :
    Entity(),
    Textured(bitmap),
    m_size(0.f, 0.f)
{
    ResetSize();
}

Sprite::~Sprite()
{

}

const Vector2f& Sprite::GetSize() const
{
    return m_size;
}

const Vector2f& Sprite::GetCenter() const
{
    return m_center;
}

const Color& Sprite::GetColor() const
{
    return m_color;
}

void Sprite::SetSize(const Vector2f& size)
{
    m_size = size;
}

void Sprite::SetSize(float width, float height)
{
    m_size = Vector2f(width, height);
}

void Sprite::SetCenter(const Vector2f& center)
{
    m_center = center;
}

void Sprite::SetCenter(float centerX, float centerY)
{
    m_center = Vector2f(centerX, centerY);
}

void Sprite::SetColor(const Color& color)
{
    m_color = color;
}

void Sprite::ResetSize()
{
    m_size = m_bitmap == nullptr ? Vector2f(0.f, 0.f) :
                                   Vector2f(m_bitmap->GetSize().x, m_bitmap->GetSize().y);
}

void Sprite::Update(const float dt)
{

}

void Sprite::Render(Renderer& renderer)
{
    if (m_bitmap != nullptr) {
        prepareRenderer(renderer);
        renderer.DrawBitmap(m_bitmap, m_source, FloatRect(m_center * -1.f, m_size), m_color);
    }
}
