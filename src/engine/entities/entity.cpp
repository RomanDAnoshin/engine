#include "engine/entities/entity.h"
using namespace engine;

Entity::Entity() :
    Object(),
    Transformable()
{
    
}

Entity::~Entity() = default;

void Entity::Update(const float dt)
{
    Object::Update(dt);
}

void Entity::prepareRenderer(Renderer& renderer)
{
    Transform transform(m_position, m_scale, m_rotation);
    transform.Compose(renderer.GetTransform());
    renderer.SetTransform(transform);
}
