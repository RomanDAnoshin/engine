#include "entities/entity.h"
using namespace engine;

Entity::Entity() :
    Object(),
    Transformable()
{
    
}

Entity::~Entity()
{

}

void Entity::prepareRenderer(Renderer& renderer)
{
    Transform transform = m_transform;
    transform.Compose(renderer.GetTransform());
    renderer.SetTransform(transform);
}
