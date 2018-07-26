#include "text/font.h"
using namespace engine;

namespace engine
{
    const Font* Font::baseFont = nullptr;
}

Font::Font() :
    m_font(nullptr),
    m_size(8)
{
    m_font = al_create_builtin_font();
}

Font::Font(const std::string& filename, int size) :
    m_font(nullptr)
{
    LoadFromFile(filename, size);
}

Font::~Font()
{
    al_destroy_font(m_font);
}

void Font::LoadFromFile(const std::string& filename, int size)
{
    al_destroy_font(m_font);
    m_size = size;
    m_filename = filename;
    m_font = al_load_ttf_font(m_filename.c_str(), m_size, 0);
    if (m_font == nullptr)
        throw std::invalid_argument("Failed to load font " + filename);
}

void Font::Clear()
{
    al_destroy_font(m_font);
    m_font = al_create_builtin_font();
    m_size = 8;
}

int Font::GetSize() const
{
    return m_size;
}

int Font::GetHeight() const
{
    return al_get_font_line_height(m_font);
}

Vector2u Font::GetTextSize(const std::string& text) const
{
    Vector2u size;
    size.x = static_cast<unsigned>(al_get_text_width(m_font, text.c_str()));
    size.y = static_cast<unsigned>(GetHeight());
    return size;
}

//void Font::Draw(const Text* text, const Vector2f& position) const
//{
//    const Color& color = text->GetTextColor();
//    ALLEGRO_COLOR c = al_map_rgba(color.r, color.g, color.b, color.a);

//    al_draw_text(m_font, c, position.x, position.y, text->GetHorizontalAlign(), text->GetText().c_str());
//}

void Font::initBaseFont()
{
    baseFont = new Font();
}

const Font* Font::GetBaseFont()
{
    if (baseFont == nullptr)
        initBaseFont();
    return baseFont;
}
