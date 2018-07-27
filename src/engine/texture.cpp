#include "engine/texture.h"
using namespace engine;

Bitmap::Bitmap(const std::string &file) :
    m_bitmap(nullptr)
{
    if (!file.empty())
        LoadFromFile(file);
}

Bitmap::~Bitmap()
{
    Clear();
}

const ALLEGRO_BITMAP* Bitmap::GetBitmapHandle() const
{
    return m_bitmap;
}

const Vector2i& Bitmap::GetSize() const
{
    return m_size;
}

void Bitmap::LoadFromFile(const std::string &file)
{
    Clear();
    m_bitmap = al_load_bitmap(file.c_str());
    if (m_bitmap == nullptr)
        throw std::runtime_error("Failed to load texture " + file);
    m_size = Vector2i(al_get_bitmap_width(m_bitmap), al_get_bitmap_height(m_bitmap));
}

void Bitmap::Clear()
{
    if (m_bitmap) {
        al_destroy_bitmap(m_bitmap);
        m_bitmap = nullptr;
        m_size = Vector2i(0, 0);
    }
}

Textured::Textured(const Bitmap* bitmap) :
    m_bitmap(nullptr)
{
    SetBitmap(bitmap);
}

Textured::~Textured()
{

}

const Bitmap* Textured::GetBitmap() const
{
    return m_bitmap;
}

const IntRect& Textured::GetSourceRect() const
{
    return m_source;
}

void Textured::SetBitmap(const Bitmap* bitmap)
{
    m_bitmap = bitmap;
    ResetSource();
}

void Textured::SetSourceRect(const IntRect &source)
{
    m_source = source;
}

void Textured::ResetSource()
{
    if (m_bitmap != nullptr)
        m_source = IntRect(Vector2i(0, 0), m_bitmap->GetSize());
}
