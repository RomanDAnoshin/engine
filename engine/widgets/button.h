#ifndef BUTTON_H
#define BUTTON_H

#include "mousearea.h"
#include "label.h"

namespace engine
{

class Button : public Label, public MouseArea
{
public:
    Button(const std::string& text = "Button", const Font& font = *Font::GetBaseFont());

    virtual void HandleEvent(ALLEGRO_EVENT& event);
};

}

#endif // BUTTON_H
