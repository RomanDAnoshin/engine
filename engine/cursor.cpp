#include "cursor.h"
using namespace engine;

Cursor::Cursor(const Bitmap* bitmap) :
    m_cursor(nullptr),
    m_bitmap(bitmap)
{
    createCursor();
}

Cursor::~Cursor()
{
    al_destroy_mouse_cursor(m_cursor);
}

const ALLEGRO_MOUSE_CURSOR*Cursor::GetCursorHandle() const
{
    return m_cursor;
}

const Bitmap* Cursor::GetBitmap() const
{
    return m_bitmap;
}

const Vector2i&Cursor::GetFocus() const
{
    return m_focus;
}

void Cursor::SetBitmap(const Bitmap* bitmap)
{
    m_bitmap = bitmap;
    createCursor();
}

void Cursor::SetFocus(const Vector2i& focus)
{
    m_focus = focus;
    createCursor();
}

void Cursor::createCursor()
{
    al_destroy_mouse_cursor(m_cursor);
    m_cursor = nullptr;
    if (m_bitmap != nullptr) {
        ALLEGRO_BITMAP* bmp = const_cast<ALLEGRO_BITMAP*>(m_bitmap->GetBitmapHandle());
        m_cursor = al_create_mouse_cursor(bmp, m_focus.x, m_focus.y);
    }
}
