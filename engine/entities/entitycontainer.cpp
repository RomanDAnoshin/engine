#include "entitycontainer.h"
using namespace engine;

EntityContainer::EntityContainer() :
    Entity(),
    Container()
{

}

EntityContainer::~EntityContainer()
{

}

void EntityContainer::AddEntity(Entity* entity, unsigned order)
{
    Object* object = dynamic_cast<Object*>(entity);
    if (object == nullptr) {
        throw std::invalid_argument("Invalid entity\n");
    }
    AddObject(object, order);
}

void EntityContainer::RemoveEntity(Entity* entity, bool free)
{
    Object* object = dynamic_cast<Object*>(entity);
    if (object == nullptr) {
        throw std::invalid_argument("Invalid entity\n");
    }
    RemoveObject(object, free);
}

void EntityContainer::Update(const float dt)
{
    for (auto object : m_objects) {
        Entity* entity = dynamic_cast<Entity*>(object);
        if (entity != nullptr) {
            entity->Update(dt);
        }
    }
}

void EntityContainer::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    Transform transform = renderer.GetTransform();
    for (auto object : m_objects) {
        Entity* entity = dynamic_cast<Entity*>(object);
        if (entity != nullptr) {
            renderer.SetTransform(transform);
            entity->Render(renderer);
        }
    }
}
