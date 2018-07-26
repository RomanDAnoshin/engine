#ifndef MOUSEAREA_H
#define MOUSEAREA_H

#include <allegro5/allegro.h>
#include "event.h"
#include "globals.h"

namespace engine
{

class MouseArea
{
public:
    MouseArea();

    virtual ~MouseArea() = 0;

    virtual void HandleMouseEvent(ALLEGRO_EVENT& event, const IntRect& bounds);

    //events
    Event<>& EventClick();

    Event<>& EventMousePress();

    Event<>& EventMouseRelease();

    Event<>& EventMouseMove();

    Event<>& EventMouseEnter();

    Event<>& EventMouseLeave();

private:
    bool    m_pressed;
    bool    m_cursorInside;
    Event<> m_click;
    Event<> m_mousePress;
    Event<> m_mouseRelease;
    Event<> m_mouseMove;
    Event<> m_mouseEnter;
    Event<> m_mouseLeave;
};

}

#endif // MOUSEAREA_H
