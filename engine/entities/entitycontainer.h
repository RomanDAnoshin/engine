#ifndef ENTITYCONTAINER_H
#define ENTITYCONTAINER_H

#include "entity.h"

namespace engine
{

class EntityContainer : public Entity, private Container
{
public:
    EntityContainer();

    virtual ~EntityContainer();

    using Container::GetObjects;
    using Container::Clear;

    void AddEntity(Entity* entity, unsigned order = -1);

    void RemoveEntity(Entity *entity, bool free);

    virtual void Update(const float dt);

    virtual void Render(Renderer &renderer);
};

}

#endif // ENTITYCONTAINER_H
