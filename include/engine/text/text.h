#ifndef TEXT_H
#define TEXT_H

#include "font.h"
#include <vector>
#include <iostream>
#include <sstream>

namespace engine
{

enum class HAlignment : unsigned char
{
    Left = 0,
    Center,
    Right
};

enum class VAlignment : unsigned char
{
    Top = 0,
    Center,
    Bottom
};

class Text
{
public:
    Text(const std::string& text = "Text", const Font& font = *Font::GetBaseFont());

    virtual ~Text() = 0;

    const Font& GetFont() const;

    const Color& GetTextColor() const;

    const std::string& GetText() const;

    HAlignment GetHorizontalAlign() const;

    VAlignment GetVerticalAlign() const;

    virtual void SetFont(const Font& font);

    void SetTextColor(const Color& color);

    virtual void SetText(const std::string& text);

    void SetHorizontalAlign(HAlignment align);

    void SetVerticalAlign(VAlignment align);

    void SetAlign(HAlignment horizontal, VAlignment vertical);

protected:
    virtual void updateDrawingPoint();

    const Font* m_font;
    Color       m_textColor;
    std::string m_text;
    HAlignment  m_alignH;
    VAlignment  m_alignV;
    Vector2i    m_point;
};

class MultilineText : public Text
{
public:
    MultilineText(const std::string& text = "Text", const Font& font = *Font::GetBaseFont());

    virtual ~MultilineText() = 0;

    unsigned GetLineWidth() const;

    int GetLineSpacing() const;

    virtual void SetLineWidth(unsigned lineWidth);

    void SetLineSpacing(int lineSpacing);

    virtual void SetFont(const Font& font);

    virtual void SetText(const std::string& text);

protected:
    virtual void updateText();

    virtual void updateDrawingPoint();

    unsigned                    m_lineWidth;
    int                         m_lineSpacing;
    std::vector<std::string>    m_lines;
};

}

#endif // TEXT_H
