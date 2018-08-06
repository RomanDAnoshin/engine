#ifndef SPRITE_H
#define SPRITE_H

#include "primitives/rectangle.h"
#include "engine/texture.h"

namespace engine
{

class Sprite : public GraphicRectangle, public Textured
{
public:
    Sprite(const Bitmap* bitmap = nullptr);

    void Render(Renderer& renderer);
};

}


#endif // SPRITE_H
