#include "button.h"
#include "widgetcontainer.h"
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
    WidgetContainer* container = dynamic_cast<WidgetContainer*>(m_container);
    if (container == nullptr)
        HandleMouseEvent(event, bounds);
    else {
        IntRect rect = GetAbsoluteBounds().Intersection(container->GetAbsoluteBounds());
        HandleMouseEvent(event, rect);
    }
}

