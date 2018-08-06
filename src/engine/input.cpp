#include "engine/input.h"
using namespace engine;

namespace engine
{
    bool Input::m_keys[11] = {0};
    bool Input::m_mouse[3] = {0};
    Event<KEYBOARD> Input::m_keyPressed;
    Event<KEYBOARD> Input::m_keyReleased;
    Event<MOUSE> Input::m_mousePressed;
    Event<MOUSE> Input::m_mouseReleased;
}

void Input::HandleEvent(ALLEGRO_EVENT& event)
{
    switch (event.type) {

    case ALLEGRO_EVENT_KEY_DOWN:
        switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            setKeyPressed(KEYBOARD::ESC, true);
            m_keyPressed.Invoke(KEYBOARD::ESC);
            break;
        case ALLEGRO_KEY_UP:
            setKeyPressed(KEYBOARD::UP, true);
            m_keyPressed.Invoke(KEYBOARD::UP);
            break;
        case ALLEGRO_KEY_DOWN:
            setKeyPressed(KEYBOARD::DOWN, true);
            m_keyPressed.Invoke(KEYBOARD::DOWN);
            break;
        case ALLEGRO_KEY_LEFT:
            setKeyPressed(KEYBOARD::LEFT, true);
            m_keyPressed.Invoke(KEYBOARD::LEFT);
            break;
        case ALLEGRO_KEY_RIGHT:
            setKeyPressed(KEYBOARD::RIGHT, true);
            m_keyPressed.Invoke(KEYBOARD::RIGHT);
            break;
        case ALLEGRO_KEY_Q:
            setKeyPressed(KEYBOARD::Q, true);
            m_keyPressed.Invoke(KEYBOARD::Q);
            break;
        case ALLEGRO_KEY_E:
            setKeyPressed(KEYBOARD::E, true);
            m_keyPressed.Invoke(KEYBOARD::E);
            break;
        case ALLEGRO_KEY_W:
            setKeyPressed(KEYBOARD::W, true);
            m_keyPressed.Invoke(KEYBOARD::W);
            break;
        case ALLEGRO_KEY_S:
            setKeyPressed(KEYBOARD::S, true);
            m_keyPressed.Invoke(KEYBOARD::S);
            break;
        case ALLEGRO_KEY_A:
            setKeyPressed(KEYBOARD::A, true);
            m_keyPressed.Invoke(KEYBOARD::A);
            break;
        case ALLEGRO_KEY_D:
            setKeyPressed(KEYBOARD::D, true);
            m_keyPressed.Invoke(KEYBOARD::D);
            break;
        default:
            break;
        }
        break;

    case ALLEGRO_EVENT_KEY_UP:
        switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            setKeyPressed(KEYBOARD::ESC, false);
            m_keyReleased.Invoke(KEYBOARD::ESC);
            break;
        case ALLEGRO_KEY_UP:
            setKeyPressed(KEYBOARD::UP, false);
            m_keyReleased.Invoke(KEYBOARD::UP);
            break;
        case ALLEGRO_KEY_DOWN:
            setKeyPressed(KEYBOARD::DOWN, false);
            m_keyReleased.Invoke(KEYBOARD::DOWN);
            break;
        case ALLEGRO_KEY_LEFT:
            setKeyPressed(KEYBOARD::LEFT, false);
            m_keyReleased.Invoke(KEYBOARD::LEFT);
            break;
        case ALLEGRO_KEY_RIGHT:
            setKeyPressed(KEYBOARD::RIGHT, false);
            m_keyReleased.Invoke(KEYBOARD::RIGHT);
            break;
        case ALLEGRO_KEY_Q:
            setKeyPressed(KEYBOARD::Q, false);
            m_keyReleased.Invoke(KEYBOARD::Q);
            break;
        case ALLEGRO_KEY_E:
            setKeyPressed(KEYBOARD::E, false);
            m_keyReleased.Invoke(KEYBOARD::E);
            break;
        case ALLEGRO_KEY_W:
            setKeyPressed(KEYBOARD::W, false);
            m_keyReleased.Invoke(KEYBOARD::W);
            break;
        case ALLEGRO_KEY_S:
            setKeyPressed(KEYBOARD::S, false);
            m_keyReleased.Invoke(KEYBOARD::S);
            break;
        case ALLEGRO_KEY_A:
            setKeyPressed(KEYBOARD::A, false);
            m_keyReleased.Invoke(KEYBOARD::A);
            break;
        case ALLEGRO_KEY_D:
            setKeyPressed(KEYBOARD::D, false);
            m_keyReleased.Invoke(KEYBOARD::D);
            break;
        default:
            break;
        }
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        switch (event.mouse.button) {
        case 1:
            setMousePressed(MOUSE::LMB, true);
            m_mousePressed.Invoke(MOUSE::LMB);
            break;
        case 2:
            setMousePressed(MOUSE::RMB, true);
            m_mousePressed.Invoke(MOUSE::RMB);
            break;
        case 3:
            setMousePressed(MOUSE::WHEEL, true);
            m_mousePressed.Invoke(MOUSE::WHEEL);
            break;
        default:
            break;
        }
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        switch (event.mouse.button) {
        case 1:
            setMousePressed(MOUSE::LMB, false);
            m_mouseReleased.Invoke(MOUSE::LMB);
            break;
        case 2:
            setMousePressed(MOUSE::RMB, false);
            m_mouseReleased.Invoke(MOUSE::RMB);
            break;
        case 3:
            setMousePressed(MOUSE::WHEEL, false);
            m_mouseReleased.Invoke(MOUSE::WHEEL);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

bool Input::IsKeyPressed(KEYBOARD key)
{
    return m_keys[static_cast<unsigned char>(key)];
}

bool Input::IsMouseButtonPressed(MOUSE button)
{
    return m_mouse[static_cast<unsigned char>(button)];
}

Vector2i Input::GetMousePosition()
{
    Vector2i pos;
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    pos.x = state.x;
    pos.y = state.y;
    return pos;
}

Event<KEYBOARD>&Input::EventKeyPressed()
{
    return m_keyPressed;
}

Event<KEYBOARD>&Input::EventKeyReleased()
{
    return m_keyReleased;
}

Event<MOUSE>&Input::EventMousePressed()
{
    return m_mousePressed;
}

Event<MOUSE>&Input::EventMouseReleased()
{
    return m_mouseReleased;
}

Input::Input()
{

}

void Input::setKeyPressed(KEYBOARD key, bool state)
{
    m_keys[static_cast<unsigned char>(key)] = state;
}

void Input::setMousePressed(MOUSE button, bool state)
{
    m_mouse[static_cast<unsigned char>(button)] = state;
}
