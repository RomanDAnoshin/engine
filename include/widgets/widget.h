#ifndef WIDGET_H
#define WIDGET_H

#include "entities/primitives/primitive.h"

namespace engine
{

enum class Anchor : unsigned char
{
    None = 0x00,
    Top = 0x01,
    Left = 0x02,
    Bottom = 0x04,
    Right = 0x08,
    All = Top | Left | Bottom | Right,
};

inline Anchor operator | (Anchor lhs, Anchor rhs) {
    return (Anchor)(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
}

inline Anchor& operator |= (Anchor& lhs, Anchor rhs) {
    lhs = (Anchor)(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
    return lhs;
}

inline Anchor operator & (Anchor lhs, Anchor rhs) {
    return (Anchor)(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
}

class Widget : public Object
{
public:
    Widget();

    virtual ~Widget();

    const Color& GetBackColor() const;

    const IntRect& GetBounds() const;

    IntRect GetAbsoluteBounds() const;

    const Vector2i& GetPosition() const;

    Vector2i GetAbsolutePosition() const;

    const Vector2i& GetSize() const;

    const BorderStyle& GetBorderStyle() const;

    Anchor GetAnchor() const;

    void SetBackColor(const Color& backColor);

    void SetBounds(const IntRect& bounds);

    void SetBounds(const Vector2i& position, const Vector2i& size);

    void SetBounds(int x, int y, int width, int height);

    void SetPosition(const Vector2i& position);

    void SetPosition(int x, int y);

    void SetSize(const Vector2i& size);

    void SetSize(int width, int height);

    void SetBorderStyle(const BorderStyle& style);

    void SetAnchor(Anchor anchor);

    virtual void HandleEvent(ALLEGRO_EVENT& event);

    virtual void Render(Renderer& renderer);

    Event<const IntRect&>& EventBoundsChanged();

    Event<const Vector2i&>& EventPositionChanged();

    Event<const Vector2i&>& EventSizeChanged();

protected:
    virtual void boundsChanged(const IntRect& oldValue);

    virtual void positionChanged();

    virtual void sizeChanged();

    virtual void resize(const Vector2i& oldSize, const Vector2i& newSize);

    Color       m_backColor;
    IntRect     m_bounds;
    BorderStyle m_borderStyle;
    Anchor      m_anchor;

private:
    Event<const IntRect&>   m_boundsChanged;
    Event<const Vector2i&>  m_positionChanged;
    Event<const Vector2i&>  m_sizeChanged;

    friend class WidgetContainer;
};

}

#endif // WIDGET_H
