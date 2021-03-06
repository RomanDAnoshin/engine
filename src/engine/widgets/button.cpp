#include "engine/widgets/button.h"
using namespace engine;

Button::Button(const std::string& text, const Font& font) :
    Label(text, font),
    MouseArea()
{
    m_backColor = Color(192, 192, 192);
    m_borderStyle = BorderStyle(Color(0, 0, 0), 1.f);
    SetAlign(HAlignment::Center, VAlignment::Center);
}

void Button::HandleEvent(ALLEGRO_EVENT& event)
{
    auto bounds = GetAbsoluteBounds();
    Widget* container = dynamic_cast<Widget*>(m_container);
    if (container == nullptr) {
        HandleMouseEvent(event, bounds);
    } else {
        IntRect rect = GetAbsoluteBounds().GetIntersection(container->GetAbsoluteBounds());
        HandleMouseEvent(event, rect);
    }
}

