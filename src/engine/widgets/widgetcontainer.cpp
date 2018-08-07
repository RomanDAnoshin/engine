#include "engine/widgets/widgetcontainer.h"
using namespace engine;

WidgetContainer::WidgetContainer() :
    Widget(),
    Container()
{

}

void WidgetContainer::AddWidget(Widget* widget, unsigned order)
{
    Object* object = dynamic_cast<Object*>(widget);
    if (object == nullptr) {
        throw std::invalid_argument("Invalid widget\n");
    }
    AddObject(object, order);
}

void WidgetContainer::RemoveWidget(Widget* widget)
{
    Object* object = dynamic_cast<Object*>(widget);
    if (object == nullptr) {
        throw std::invalid_argument("Invalid widget\n");
    }
    RemoveObject(object);
}

void WidgetContainer::HandleEvent(ALLEGRO_EVENT& event)
{
    Widget::HandleEvent(event);
    for (auto object : m_objects) {
        Widget* widget = dynamic_cast<Widget*>(object);
        if (widget != nullptr) {
            widget->HandleEvent(event);
        }
    }
}

void WidgetContainer::Update(const float dt)
{
    Widget::Update(dt);
    for (auto object : m_objects) {
        Widget* widget = dynamic_cast<Widget*>(object);
        if (widget != nullptr) {
            widget->Update(dt);
        }
    }
}

void WidgetContainer::Render(Renderer& renderer)
{
    Widget::Render(renderer);
    auto absRect = GetAbsoluteBounds();
    for (auto object : m_objects) {
        Widget* widget = dynamic_cast<Widget*>(object);
        if (widget != nullptr) {
            renderer.SetClippingRectangle(absRect);
            widget->Render(renderer);
        }
    }
    renderer.ResetClippingRectangle();
}

void WidgetContainer::boundsChanged(const IntRect& oldValue)
{
    Widget::boundsChanged(oldValue);
    for (auto object : m_objects) {
        Widget* widget = dynamic_cast<Widget*>(object);
        if (widget != nullptr) {
            widget->resize(oldValue.size, m_bounds.size);
        }
    }
}
