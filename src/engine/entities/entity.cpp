#include "engine/entities/entity.h"
using namespace engine;

Entity::Entity() :
    Object(),
    Transformable()
{
    
}
Entity::~Entity()
{

}

void Entity::Update(const float dt)
{
    Object::Update(dt);
}

void Entity::prepareRenderer(Renderer& renderer)
{
    Transform transform = m_transform;
    transform.Compose(renderer.GetTransform());
    renderer.SetTransform(transform);
}
