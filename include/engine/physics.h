#ifndef PHYSICS_H
#define PHYSICS_H

#include "globals.h"
#include "entities/entity.h"
#include <vector>
#include <Box2D/Box2D.h>

namespace engine
{

class Physics
{
public:
    Physics();

    virtual void Update(const float dt) = 0;
};

class Physics_Box2D : public Physics
{
public:
    Physics_Box2D();

    int GetVelocityIterations() const;

    int GetPositionIterations() const;

    b2World* GetWorld();

    float GetScale() const;

    void SetVelocityIterations(int velIterations);

    void SetPositionIterations(int posIterations);

    void SetWorld(b2World* world);

    void SetScale(float scale);

    void Update(const float dt);

protected:
    int         m_velIterations;
    int         m_posIterations;
    b2World*    m_world;
    float       m_scale;
};

}

#endif // PHYSICS_H
