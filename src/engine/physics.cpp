#include "engine/physics.h"
using namespace engine;

Physics::Physics()
{

}

Physics_Box2D::Physics_Box2D() :
    Physics(),
    m_velIterations(6),
    m_posIterations(2),
    m_world(nullptr),
    m_scale(30.f)
{

}

int Physics_Box2D::GetVelocityIterations() const
{
    return m_velIterations;
}

int Physics_Box2D::GetPositionIterations() const
{
    return m_posIterations;
}

b2World* Physics_Box2D::GetWorld()
{
    return m_world;
}

float Physics_Box2D::GetScale() const
{
    return m_scale;
}

void Physics_Box2D::SetVelocityIterations(int velIterations)
{
    m_velIterations = velIterations;
}

void Physics_Box2D::SetPositionIterations(int posIterations)
{
    m_posIterations = posIterations;
}

void Physics_Box2D::SetWorld(b2World *world)
{
    m_world = world;
}

void Physics_Box2D::SetScale(float scale)
{
    m_scale = scale;
}

void Physics_Box2D::Update(const float dt)
{
    m_world->Step(dt, m_velIterations, m_posIterations);
    for (const b2Body* ptr = m_world->GetBodyList(); ptr != nullptr; ptr = ptr->GetNext()) {
        Entity* entity = static_cast<Entity*>(ptr->GetUserData());
        if (entity != nullptr) {
            entity->SetRotationRad(ptr->GetAngle());
            entity->SetPosition(ptr->GetPosition().x * m_scale, ptr->GetPosition().y * m_scale);
        }
    }
}

