#ifndef TEXTURE_H
#define TEXTURE_H

#include "common/rect.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdexcept>
#include <string>

namespace engine
{

class Bitmap
{
public:
    Bitmap(const std::string& file = std::string());

    virtual ~Bitmap();

    const ALLEGRO_BITMAP* GetBitmapHandle() const;

    const Vector2i& GetSize() const;

    void LoadFromFile(const std::string& file);

    void Clear();

protected:
    ALLEGRO_BITMAP* m_bitmap;
    Vector2i        m_size;

private:
    friend class Renderer;
};

class Textured
{
public:
    Textured(const Bitmap* bitmap = nullptr);

    virtual ~Textured() = 0;

    const Bitmap* GetBitmap() const;

    const IntRect& GetSourceRect() const;

    void SetBitmap(const Bitmap* bitmap);

    void SetSourceRect(const IntRect& source);

    void ResetSource();

protected:
    const Bitmap*   m_bitmap;
    IntRect         m_source;
};

}

#endif // TEXTURE_H
