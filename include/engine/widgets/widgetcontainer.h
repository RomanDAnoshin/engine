#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include "widget.h"

namespace engine
{

class WidgetContainer : public Widget, private Container
{
public:
    WidgetContainer();

    virtual ~WidgetContainer() = default;

    using Container::GetObjects;
    using Container::Clear;

    void AddWidget(Widget* widget, unsigned order = -1);

    void RemoveWidget(Widget* widget);

    virtual void HandleEvent(ALLEGRO_EVENT& event);

    virtual void Update(const float dt);

    virtual void Render(Renderer &renderer);

protected:
    virtual void boundsChanged(const IntRect& oldValue);
};

}

#endif // WIDGETCONTAINER_H
