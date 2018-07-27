#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "engine/texture.h"

namespace engine
{

class Sprite : public Entity, public Textured
{
public:
    Sprite(const Bitmap* bitmap = nullptr);

    virtual ~Sprite();

    const Vector2f& GetSize() const;

    const Vector2f& GetCenter() const;

    const Color& GetColor() const;

    void SetSize(const Vector2f& size);

    void SetSize(float width, float height);

    void SetCenter(const Vector2f& center);

    void SetCenter(float centerX, float centerY);

    void SetColor(const Color& color);

    void ResetSize();

    void Update(const float dt);

    void Render(Renderer& renderer);

protected:
    Vector2f    m_size;
    Vector2f    m_center;
    Color       m_color;
};

}


#endif // SPRITE_H
