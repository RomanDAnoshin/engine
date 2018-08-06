#ifndef SCENE_H
#define SCENE_H

#include "entities/entitycontainer.h"
#include "widgets/widgetcontainer.h"
#include "physics.h"

namespace engine
{

class Scene
{
public:
    Scene();

    virtual ~Scene();

    EntityContainer& GetRootEntity();

    WidgetContainer& GetRootWidget();

    Physics* GetPhysics() const;

    void SetPhysics(Physics* physics);

    virtual void HandleEvent(ALLEGRO_EVENT& event);

    virtual void Update(const float dt);

    virtual void Render(Renderer& renderer);

protected:
    EntityContainer m_rootEntity;
    WidgetContainer m_rootWidget;
    Physics*        m_physics;
};

}

#endif // SCENE_H
