#include "widgets/label.h"
using namespace engine;

Label::Label(const std::string& text, const Font& font) :
    Widget(),
    MultilineText(text, font),
    m_margin(3),
    m_multiline(false)
{
    m_alignH = HAlignment::Left;
    m_backColor = Color(255,255,255,0);
    updateDrawingPoint();
}

const Margin& Label::GetMargin() const
{
    return m_margin;
}

bool Label::IsMultiline() const
{
    return m_multiline;
}

void Label::SetMargin(const Margin& margin)
{
    m_margin = margin;
    updateDrawingPoint();
}

void Label::SetMargin(int left, int top, int right, int bottom)
{
    Margin margin(left, top, right, bottom);
    SetMargin(margin);
}

void Label::SetMargin(int all)
{
    Margin margin(all, all, all, all);
    SetMargin(margin);
}

void Label::SetMultiline(bool multiline)
{
    if (m_multiline != multiline) {
        m_multiline = multiline;
        updateText();
    }
}

void Label::HandleEvent(ALLEGRO_EVENT& event)
{

}

void Label::Render(Renderer& renderer)
{
    Widget::Render(renderer);
    auto absPos = GetAbsolutePosition();
    const IntRect& a = renderer.GetClippingRectangle();
    IntRect b(absPos.x + m_margin.left, absPos.y + m_margin.top,
              m_bounds.size.x - m_margin.left - m_margin.right,
              m_bounds.size.y - m_margin.top - m_margin.bottom);

    IntRect res = a.Intersection(b);
    renderer.SetClippingRectangle(res);
    int x = m_point.x + absPos.x;
    int y = m_point.y + absPos.y;
    if (m_multiline) {
        int height = m_font->GetHeight() + m_lineSpacing;
        for (size_t i = 0; i != m_lines.size(); ++i) {
            renderer.DrawText(m_font, m_lines[i], Vector2i(x, y + height * i), m_alignH, m_textColor);
        }
    } else {
        renderer.DrawText(m_font, m_text, Vector2i(x, y), m_alignH, m_textColor);
    }
}

void Label::SetLineWidth(unsigned lineWidth)
{
    MultilineText::SetLineWidth(lineWidth);
}

void Label::boundsChanged(const IntRect& oldValue)
{
    Widget::boundsChanged(oldValue);
    SetLineWidth(m_bounds.size.x - m_margin.left - m_margin.right);
    updateDrawingPoint();
}

void Label::updateDrawingPoint()
{
    switch (m_alignH) {
    case HAlignment::Center:
        m_point.x = m_margin.left - m_margin.right + m_bounds.size.x / 2;
        break;
    case HAlignment::Right:
        m_point.x = m_bounds.size.x - m_margin.right;
        break;
    default:
        m_point.x = m_margin.left;
        break;
    }
    int textHeight = m_multiline ? m_lines.size() * (m_font->GetHeight() + m_lineSpacing) - m_lineSpacing :
                                   m_font->GetHeight();
    switch (m_alignV) {
    case VAlignment::Center:
        m_point.y = m_margin.top - m_margin.bottom + (m_bounds.size.y - textHeight) / 2;
        break;
    case VAlignment::Bottom:
        m_point.y = m_bounds.size.y - m_margin.bottom - textHeight;
        break;
    default:
        m_point.y = m_margin.top;
        break;
    }
}
