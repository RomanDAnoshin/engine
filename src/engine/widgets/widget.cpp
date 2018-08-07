#include "engine/widgets/widget.h"
using namespace engine;

Widget::Widget() :
    Object(),
    m_bounds(0.f, 0.f, 64.f, 32.f),
    m_anchor(Anchor::Top | Anchor::Left)
{

}

const Color& Widget::GetBackColor() const
{
    return m_backColor;
}

const IntRect& Widget::GetBounds() const
{
    return m_bounds;
}

IntRect Widget::GetAbsoluteBounds() const
{
    return IntRect(GetAbsolutePosition(), m_bounds.size);
}

const Vector2i& Widget::GetPosition() const
{
    return m_bounds.pos;
}

Vector2i Widget::GetAbsolutePosition() const
{
    Widget* container = dynamic_cast<Widget*>(m_container);
    if (container == nullptr) {
        return GetPosition();
    }
    return GetPosition() + container->GetAbsolutePosition();
}

const Vector2i& Widget::GetSize() const
{
    return m_bounds.size;
}

const BorderStyle& Widget::GetBorderStyle() const
{
    return m_borderStyle;
}

Anchor Widget::GetAnchor() const
{
    return m_anchor;
}

void Widget::SetBackColor(const Color& backColor)
{
    m_backColor = backColor;
}

void Widget::SetBounds(const IntRect& bounds)
{
    if (m_bounds == bounds) {
        return;
    }
    IntRect oldValue = m_bounds;
    if (m_bounds.pos != bounds.pos) {
        m_bounds.pos = bounds.pos;
        positionChanged();
    }
    if (m_bounds.size != bounds.size) {
        m_bounds.size = bounds.size;
        sizeChanged();
    }
    boundsChanged(oldValue);
}

void Widget::SetBounds(const Vector2i& position, const Vector2i& size)
{
    IntRect rect(position, size);
    SetBounds(rect);
}

void Widget::SetBounds(int x, int y, int width, int height)
{
    IntRect rect(x, y, width, height);
    SetBounds(rect);
}

void Widget::SetPosition(const Vector2i& position)
{
    IntRect rect(position, m_bounds.size);
    SetBounds(rect);
}

void Widget::SetPosition(int x, int y)
{
    Vector2i position(x, y);
    SetPosition(position);
}

void Widget::SetSize(const Vector2i& size)
{
    IntRect rect(m_bounds.pos, size);
    SetBounds(rect);
}

void Widget::SetSize(int width, int height)
{
    Vector2i size(width, height);
    SetSize(size);
}

void Widget::SetBorderStyle(const BorderStyle& style)
{
    m_borderStyle = style;
}

void Widget::SetAnchor(Anchor anchor)
{
    m_anchor = anchor;
}

void Widget::HandleEvent(ALLEGRO_EVENT& event)
{

}

void Widget::Update(const float dt)
{
    Object::Update(dt);
}

void Widget::Render(Renderer& renderer)
{
    auto absPos = GetAbsolutePosition();
    renderer.FillRectangle(absPos, m_bounds.size, m_backColor);
    if (m_borderStyle.visible) {
        renderer.DrawRectangle(absPos, m_bounds.size, m_borderStyle.color, m_borderStyle.thickness);
    }
}

void Widget::boundsChanged(const IntRect& oldValue)
{
    m_boundsChanged.Invoke(m_bounds);
}

void Widget::positionChanged()
{
    m_positionChanged.Invoke(m_bounds.pos);
}

void Widget::sizeChanged()
{
    m_sizeChanged.Invoke(m_bounds.size);
}

void Widget::resize(const Vector2i& oldSize, const Vector2i& newSize)
{
    IntRect oldValue = m_bounds;
    if (m_anchor == Anchor::None) {
        int dh = newSize.y - oldSize.y;
        int dw = newSize.x - oldSize.x;
        m_bounds.pos.y += dh / 2;
        m_bounds.pos.x += dw / 2;
        return;
    }
    if ((m_anchor & Anchor::Bottom) == Anchor::Bottom) {
        int dh = newSize.y - oldSize.y;
        if ((m_anchor & Anchor::Top) != Anchor::Top) {
            m_bounds.pos.y += dh;
        } else {
            m_bounds.size.y += dh;
        }
    }
    if ((m_anchor & Anchor::Right) == Anchor::Right) {
        int dw = newSize.x - oldSize.x;
        if ((m_anchor & Anchor::Left) != Anchor::Left) {
            m_bounds.pos.x += dw;
        } else {
            m_bounds.size.x += dw;
        }
    }
    if (m_bounds.size.x < 0) {
        m_bounds.size.x = 0;
    }
    if (m_bounds.size.y < 0) {
        m_bounds.size.y = 0;
    }
    if (m_bounds != oldValue) {
        boundsChanged(oldValue);
    }
}

Event<const IntRect&>& Widget::EventBoundsChanged()
{
    return m_boundsChanged;
}

Event<const Vector2i&>& Widget::EventPositionChanged()
{
    return m_positionChanged;
}

Event<const Vector2i&>& Widget::EventSizeChanged()
{
    return m_sizeChanged;
}
