#ifndef ENTITY_H
#define ENTITY_H

#include "engine/object.h"

namespace engine
{

class Entity : public Object, public Transformable
{
public:
    Entity();

    virtual ~Entity() = 0;

    virtual void Update(const float dt);

    virtual void Render(Renderer& renderer) = 0;

protected:
    void prepareRenderer(Renderer& renderer);
};

}

#endif // ENTITY_H
