#ifndef LABEL_H
#define LABEL_H

#include "engine/text/text.h"
#include "widget.h"

namespace engine
{

struct Margin
{
    Margin() : left(0), top(0), right(0), bottom(0) { }
    Margin(int left, int top, int right, int bottom) :
        left(left), top(top), right(right), bottom(bottom) { }
    Margin(int all) :
        left(all), top(all), right(all), bottom(all) { }
    int left, top, right, bottom;
};

class Label : public Widget, public MultilineText
{
public:
    Label(const std::string& text = "Label", const Font& font = *Font::GetBaseFont());

    const Margin& GetMargin() const;

    bool IsMultiline() const;

    void SetMargin(const Margin& margin);

    void SetMargin(int left, int top, int right, int bottom);

    void SetMargin(int all);

    void SetMultiline(bool multiline);

    virtual void HandleEvent(ALLEGRO_EVENT& event);

    virtual void Render(Renderer& renderer);

protected:
    virtual void SetLineWidth(unsigned lineWidth);

    virtual void boundsChanged(const IntRect& oldValue);

    virtual void updateDrawingPoint();

    Margin  m_margin;
    bool    m_multiline;
};

}

#endif // LABEL_H
