#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include "tools/event.h"
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
    A,
    D,
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

    static void HandleEvent(ALLEGRO_EVENT& event);

    static bool IsKeyPressed(KEYBOARD key);

    static bool IsMouseButtonPressed(MOUSE button);

    static Vector2i GetMousePosition();

    static Event<KEYBOARD>& EventKeyPressed();

    static Event<KEYBOARD>& EventKeyReleased();

    static Event<MOUSE>& EventMousePressed();

    static Event<MOUSE>& EventMouseReleased();

private:
    Input();

    static void setKeyPressed(KEYBOARD key, bool state);

    static void setMousePressed(MOUSE button, bool state);

    static bool             m_keys[11];
    static bool             m_mouse[3];
    static Event<KEYBOARD>  m_keyPressed;
    static Event<KEYBOARD>  m_keyReleased;
    static Event<MOUSE>     m_mousePressed;
    static Event<MOUSE>     m_mouseReleased;
};

}

#endif // INPUT_H
