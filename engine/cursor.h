#ifndef CURSOR_H
#define CURSOR_H

#include "texture.h"

namespace engine
{

enum SYSTEM_CURSOR
{
    SYSTEM_CURSOR_NONE = 0,
    SYSTEM_CURSOR_DEFAULT,
    SYSTEM_CURSOR_ARROW,
    SYSTEM_CURSOR_BUSY,
    SYSTEM_CURSOR_QUESTION,
    SYSTEM_CURSOR_EDIT,
    SYSTEM_CURSOR_MOVE,
    SYSTEM_CURSOR_RESIZE_N,
    SYSTEM_CURSOR_RESIZE_W,
    SYSTEM_CURSOR_RESIZE_S,
    SYSTEM_CURSOR_RESIZE_E,
    SYSTEM_CURSOR_RESIZE_NW,
    SYSTEM_CURSOR_RESIZE_SW,
    SYSTEM_CURSOR_RESIZE_SE,
    SYSTEM_CURSOR_RESIZE_NE,
    SYSTEM_CURSOR_PROGRESS,
    SYSTEM_CURSOR_PRECISION,
    SYSTEM_CURSOR_LINK,
    SYSTEM_CURSOR_ALT_SELECT,
    SYSTEM_CURSOR_UNAVAILABLE
};

class Cursor
{
public:
    Cursor(const Bitmap* bitmap = nullptr);

    ~Cursor();

    const ALLEGRO_MOUSE_CURSOR* GetCursorHandle() const;

    const Bitmap* GetBitmap() const;

    const Vector2i& GetFocus() const;

    void SetBitmap(const Bitmap* bitmap);

    void SetFocus(const Vector2i& focus);

private:
    void createCursor();

    ALLEGRO_MOUSE_CURSOR*   m_cursor;
    const Bitmap*           m_bitmap;
    Vector2i                m_focus;
};

}

#endif // CURSOR_H
