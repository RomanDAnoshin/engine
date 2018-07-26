#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include "event.h"
#include "globals.h"

namespace engine
{

enum class KEYBOARD : unsigned char
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    Q,
    E,
    W,
    S,
    ESC
};

enum class MOUSE : unsigned char
{
    LMB = 0,
    RMB,
    WHEEL
};

class Input
{
public:
    Input();

    void HandleEvent(ALLEGRO_EVENT& event);

    bool IsKeyPressed(KEYBOARD key) const;

    bool IsMouseButtonPressed(MOUSE button) const;

    Vector2i GetMousePosition() const;

    Event<KEYBOARD> OnKeyPressed;

    Event<KEYBOARD> OnKeyReleased;

    Event<MOUSE> OnMousePressed;

    Event<MOUSE> OnMouseReleased;

protected:
    void setKeyPressed(KEYBOARD key, bool state);

    void setMousePressed(MOUSE button, bool state);

    bool    m_keys[9] = {0};
    bool    m_mouse[3] = {0};

};

}

#endif // INPUT_H
