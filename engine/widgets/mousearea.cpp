#include "mousearea.h"
using namespace engine;

MouseArea::MouseArea() :
    m_pressed(false),
    m_cursorInside(false)
{

}

MouseArea::~MouseArea()
{

}

void MouseArea::HandleMouseEvent(ALLEGRO_EVENT& event, const IntRect& bounds)
{
    bool inside = event.mouse.x >= bounds.pos.x && event.mouse.x <= bounds.pos.x + bounds.size.x &&
                  event.mouse.y >= bounds.pos.y && event.mouse.y <= bounds.pos.y + bounds.size.y;
    switch (event.type) {
    case ALLEGRO_EVENT_MOUSE_AXES:
        if (m_cursorInside == false && inside == true) {
            m_cursorInside = true;
            m_mouseEnter.Invoke();
        }
        else if (m_cursorInside == true && inside == false) {
            m_cursorInside = false;
            m_mouseLeave.Invoke();
        }
        else if (m_cursorInside == true && inside == true) {
            m_mouseMove.Invoke();
        }
        break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        if (event.mouse.button == 1 && inside) {
            m_mousePress.Invoke();
            m_pressed = true;
        }
        break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        if (event.mouse.button == 1 && m_pressed) {
            m_pressed = false;
            m_mouseRelease.Invoke();
            if (inside)
                m_click.Invoke();
        }
        break;
    }
}

Event<>& MouseArea::EventClick()
{
    return m_click;
}

Event<>& MouseArea::EventMousePress()
{
    return m_mousePress;
}

Event<>& MouseArea::EventMouseRelease()
{
    return m_mouseRelease;
}

Event<>& MouseArea::EventMouseMove()
{
    return m_mouseMove;
}

Event<>& MouseArea::EventMouseEnter()
{
    return m_mouseEnter;
}

Event<>& MouseArea::EventMouseLeave()
{
    return m_mouseLeave;
}
