#ifndef SIMPLETEXT_H
#define SIMPLETEXT_H

#include "entity.h"
#include "engine/text/text.h"

namespace engine
{

class SimpleText : public Entity, public Text
{
public:
    SimpleText(const std::string& text = "Simple Text", const Font& font = *Font::GetBaseFont());

    void Update(const float dt);

    void Render(Renderer& renderer);
};

}

#endif // SIMPLETEXT_H
