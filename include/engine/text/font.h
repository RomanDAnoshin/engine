#ifndef FONT_H
#define FONT_H

#include "engine/common/vector2.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <stdexcept>

namespace engine
{

class Font
{
public:
    Font();

    Font(const std::string& filename, int size = 8);

    virtual ~Font();

    void LoadFromFile(const std::string& filename, int size = 8);

    void Clear();

    int GetSize() const;

    int GetHeight() const;

    Vector2u GetTextSize(const std::string& text) const;

    static const Font* GetBaseFont();

protected:
    ALLEGRO_FONT*   m_font;
    std::string     m_filename;
    int             m_size;

private:
    static void initBaseFont();

    static const Font* baseFont;

    friend class Renderer;
};

}

#endif // FONT_H
