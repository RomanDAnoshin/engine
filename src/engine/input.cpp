#include "engine/input.h"
using namespace engine;

Input::Input()
{

}

void Input::HandleEvent(ALLEGRO_EVENT& event)
{
    switch (event.type) {

    case ALLEGRO_EVENT_KEY_DOWN:
        switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            setKeyPressed(KEYBOARD::ESC, true);
            OnKeyPressed.Invoke(KEYBOARD::ESC);
            break;
        case ALLEGRO_KEY_UP:
            setKeyPressed(KEYBOARD::UP, true);
            OnKeyPressed.Invoke(KEYBOARD::UP);
            break;
        case ALLEGRO_KEY_DOWN:
            setKeyPressed(KEYBOARD::DOWN, true);
            OnKeyPressed.Invoke(KEYBOARD::DOWN);
            break;
        case ALLEGRO_KEY_LEFT:
            setKeyPressed(KEYBOARD::LEFT, true);
            OnKeyPressed.Invoke(KEYBOARD::LEFT);
            break;
        case ALLEGRO_KEY_RIGHT:
            setKeyPressed(KEYBOARD::RIGHT, true);
            OnKeyPressed.Invoke(KEYBOARD::RIGHT);
            break;
        case ALLEGRO_KEY_Q:
            setKeyPressed(KEYBOARD::Q, true);
            OnKeyPressed.Invoke(KEYBOARD::Q);
            break;
        case ALLEGRO_KEY_E:
            setKeyPressed(KEYBOARD::E, true);
            OnKeyPressed.Invoke(KEYBOARD::E);
            break;
        case ALLEGRO_KEY_W:
            setKeyPressed(KEYBOARD::W, true);
            OnKeyPressed.Invoke(KEYBOARD::W);
            break;
        case ALLEGRO_KEY_S:
            setKeyPressed(KEYBOARD::S, true);
            OnKeyPressed.Invoke(KEYBOARD::S);
            break;
        default:
            break;
        }
        break;

    case ALLEGRO_EVENT_KEY_UP:
        switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            setKeyPressed(KEYBOARD::ESC, false);
            OnKeyReleased.Invoke(KEYBOARD::ESC);
            break;
        case ALLEGRO_KEY_UP:
            setKeyPressed(KEYBOARD::UP, false);
            OnKeyReleased.Invoke(KEYBOARD::UP);
            break;
        case ALLEGRO_KEY_DOWN:
            setKeyPressed(KEYBOARD::DOWN, false);
            OnKeyReleased.Invoke(KEYBOARD::DOWN);
            break;
        case ALLEGRO_KEY_LEFT:
            setKeyPressed(KEYBOARD::LEFT, false);
            OnKeyReleased.Invoke(KEYBOARD::LEFT);
            break;
        case ALLEGRO_KEY_RIGHT:
            setKeyPressed(KEYBOARD::RIGHT, false);
            OnKeyReleased.Invoke(KEYBOARD::RIGHT);
            break;
        case ALLEGRO_KEY_Q:
            setKeyPressed(KEYBOARD::Q, false);
            OnKeyReleased.Invoke(KEYBOARD::Q);
            break;
        case ALLEGRO_KEY_E:
            setKeyPressed(KEYBOARD::E, false);
            OnKeyReleased.Invoke(KEYBOARD::E);
            break;
        case ALLEGRO_KEY_W:
            setKeyPressed(KEYBOARD::W, false);
            OnKeyReleased.Invoke(KEYBOARD::W);
            break;
        case ALLEGRO_KEY_S:
            setKeyPressed(KEYBOARD::S, false);
            OnKeyReleased.Invoke(KEYBOARD::S);
            break;
        default:
            break;
        }
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        switch (event.mouse.button) {
        case 1:
            setMousePressed(MOUSE::LMB, true);
            OnMousePressed.Invoke(MOUSE::LMB);
            break;
        case 2:
            setMousePressed(MOUSE::RMB, true);
            OnMousePressed.Invoke(MOUSE::RMB);
            break;
        case 3:
            setMousePressed(MOUSE::WHEEL, true);
            OnMousePressed.Invoke(MOUSE::WHEEL);
            break;
        default:
            break;
        }
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        switch (event.mouse.button) {
        case 1:
            setMousePressed(MOUSE::LMB, false);
            OnMouseReleased.Invoke(MOUSE::LMB);
            break;
        case 2:
            setMousePressed(MOUSE::RMB, false);
            OnMouseReleased.Invoke(MOUSE::RMB);
            break;
        case 3:
            setMousePressed(MOUSE::WHEEL, false);
            OnMouseReleased.Invoke(MOUSE::WHEEL);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

bool Input::IsKeyPressed(KEYBOARD key) const
{
    return m_keys[static_cast<unsigned char>(key)];
}

bool Input::IsMouseButtonPressed(MOUSE button) const
{
    return m_mouse[static_cast<unsigned char>(button)];
}

Vector2i Input::GetMousePosition() const
{
    Vector2i pos;
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    pos.x = state.x;
    pos.y = state.y;
    return pos;
}

void Input::setKeyPressed(KEYBOARD key, bool state)
{
    m_keys[static_cast<unsigned char>(key)] = state;
}

void Input::setMousePressed(MOUSE button, bool state)
{
    m_mouse[static_cast<unsigned char>(button)] = state;
}
