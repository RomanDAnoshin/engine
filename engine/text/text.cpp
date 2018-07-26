#include "text.h"
using namespace engine;



Text::Text(const std::string& text, const Font& font) :
    m_font(&font),
    m_textColor(0, 0, 0),
    m_text(text),
    m_alignH(HAlignment::Center),
    m_alignV(VAlignment::Center),
    m_point(0.f, 0.f)
{
    updateDrawingPoint();
}

Text::~Text()
{

}

const Font& Text::GetFont() const
{
    return *m_font;
}

const Color&Text::GetTextColor() const
{
    return m_textColor;
}

const std::string&Text::GetText() const
{
    return m_text;
}

HAlignment Text::GetHorizontalAlign() const
{
    return m_alignH;
}

VAlignment Text::GetVerticalAlign() const
{
    return m_alignV;
}

void Text::SetFont(const Font& font)
{
    m_font = &font;
    updateDrawingPoint();
}

void Text::SetTextColor(const Color& color)
{
    m_textColor = color;
}

void Text::SetText(const std::string& text)
{
    m_text = text;
    updateDrawingPoint();
}

void Text::SetHorizontalAlign(HAlignment align)
{
    m_alignH = align;
    updateDrawingPoint();
}

void Text::SetVerticalAlign(VAlignment align)
{
    m_alignV = align;
    updateDrawingPoint();
}

void Text::SetAlign(HAlignment horizontal, VAlignment vertical)
{
    m_alignH = horizontal;
    m_alignV = vertical;
    updateDrawingPoint();
}

void Text::updateDrawingPoint()
{
    m_point.x = 0;
    switch (m_alignV) {
    case VAlignment::Center:
        m_point.y = -m_font->GetTextSize(m_text).y / 2;
        break;
    case VAlignment::Bottom:
        m_point.y = -m_font->GetTextSize(m_text).y;
        break;
    default:
        m_point.y = 0;
        break;
    }
}

MultilineText::MultilineText(const std::string& text, const Font& font) :
    Text(text, font),
    m_lineWidth(0),
    m_lineSpacing(0)
{
    updateText();
}

MultilineText::~MultilineText()
{

}

unsigned MultilineText::GetLineWidth() const
{
    return m_lineWidth;
}

int MultilineText::GetLineSpacing() const
{
    return m_lineSpacing;
}

void MultilineText::SetLineWidth(unsigned lineWidth)
{
    if (m_lineWidth != lineWidth) {
        m_lineWidth = lineWidth;
        updateText();
    }
}

void MultilineText::SetLineSpacing(int lineSpacing)
{
    m_lineSpacing = lineSpacing;
}

void MultilineText::SetFont(const Font& font)
{
    Text::SetFont(font);
    updateText();
}

void MultilineText::SetText(const std::string& text)
{
    if (m_text != text) {
        Text::SetText(text);
        updateText();
    }
}

void MultilineText::updateText()
{
    m_lines.clear();
    if (m_text.empty()) {
        return;
    }
    if (m_lineWidth == 0) {
        m_lines.push_back(m_text);
        return;
    }
    if (m_lineWidth < m_font->GetTextSize(std::string(1, m_text.front())).x) {
        return;
    }
    std::stringstream buffer;
    for (size_t i = 0; i < m_text.length(); ) {
        int cplen = 1;
        if ((m_text[i] & 0xf8) == 0xf0) cplen = 4;
        else if ((m_text[i] & 0xf0) == 0xe0) cplen = 3;
        else if ((m_text[i] & 0xe0) == 0xc0) cplen = 2;
        if ((i + cplen) > m_text.length()) cplen = 1;

        std::string c = m_text.substr(i, cplen);
        i += cplen;

        if (c == "\n") {
            m_lines.push_back(buffer.str());
            buffer.str(std::string());
            continue;
        }
        buffer << c;
        std::string str = buffer.str();
        if (m_font->GetTextSize(str).x > m_lineWidth) {
            str.pop_back();
            m_lines.push_back(str);
            buffer.str(std::string());
            buffer << c;
        }
    }
    std::string str = buffer.str();
    if (!str.empty()) {
        m_lines.push_back(str);
    }
}

void MultilineText::updateDrawingPoint()
{
    int textHeight = m_lines.size() * (m_font->GetHeight() + m_lineSpacing) - m_lineSpacing;
    m_point.x = 0;
    switch (m_alignV) {
    case VAlignment::Center:
        m_point.y = -textHeight / 2;
        break;
    case VAlignment::Bottom:
        m_point.y = -textHeight;
        break;
    default:
        m_point.y = 0;
        break;
    }
}
