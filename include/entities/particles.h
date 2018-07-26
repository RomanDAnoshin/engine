#ifndef PARTICLES_H
#define PARTICLES_H

#include "texture.h"
#include "entity.h"
#include <list>
#include <cmath>

namespace engine
{

class ParticleEmitter : public Entity, public Textured
{
public:
    ParticleEmitter();

    virtual ~ParticleEmitter();

    const Vector2f& GetForce() const;

    const Vector2<Color>& GetStartColor() const;

    const Vector2<Color>& GetFinishColor() const;

    const Vector2f& GetStartRadius() const;

    const Vector2f& GetFinishRadius() const;

    const Vector2f& GetVelocity() const;

    const Vector2f& GetLifetime() const;

    const Vector2f& GetPeriod() const;

    size_t GetParticleCount() const;

    bool IsStopped() const;

    bool IsLooped() const;

    void SetForce(const Vector2f& force);

    void SetForce(float forceX, float forceY);

    void SetColor(const Color& color);

    void SetRandomColor(const Vector2<Color>& color);

    void SetRandomColor(const Color& from, const Color& to);

    void SetRadius(float radius);

    void SetRandomRadius(const Vector2f& radius);

    void SetRandomRadius(float from, float to);

    void SetDynamicColor(const Color& start, const Color& finish);

    void SetDynamicRandomColor(const Vector2<Color>& start, const Vector2<Color>& finish);

    void SetDynamicRadius(float start, float finish);

    void SetDynamicRandomRadius(const Vector2f& start, const Vector2f& finish);

    void SetVelocity(float velocity);

    void SetRandomVelocity(const Vector2f& velocity);

    void SetRandomVelocity(float from, float to);

    void SetLifetime(float lifeTime);

    void SetRandomLifetime(const Vector2f& lifeTime);

    void SetRandomLifetime(float from, float to);

    void SetPeriod(float period);

    void SetRandomPeriod(const Vector2f& period);

    void SetRandomPeriod(float from, float to);

    void SetParticleCount(size_t count);

    void SetStopped(bool stopped);

    void SetLooped(bool looped);

    void Update(const float dt);

    void Render(Renderer& renderer);

protected:
    struct Particle
    {
        Vector2f        position;
        Vector2f        velocity;
        Vector2<Color>  colorRange;
        Vector2f        radiusRange;
        Color           color;
        float           radius;
        float           lifetime;
    };

    float randomf(float from, float to) {
        return ((to - from) * ((float)std::rand() / RAND_MAX)) + from;
    }

    int randomi(int from, int to) {
        return from + (std::rand() % (to - from + 1));
    }

    virtual void generate(Particle* p) = 0;

    bool            m_dynColor;
    bool            m_dynRadius;
    Vector2<Color>  m_startColor;
    Vector2<Color>  m_finishColor;
    Vector2f        m_startRadius;
    Vector2f        m_finishRadius;
    Vector2f        m_velocity;
    Vector2f        m_lifetime;
    Vector2f        m_force;
    Vector2f        m_period;
    float           m_timeToEmit;
    size_t          m_count;
    size_t          m_deadCount;
    bool            m_looped;
    bool            m_stopped;

    std::list<Particle*>    m_alive;
    std::list<Particle*>    m_dead;
};


class PointParticleEmitter : public ParticleEmitter
{
public:
    PointParticleEmitter();

    Vector2f GetAngleDeg() const;

    const Vector2f& GetAngleRad() const;

    void SetAngleDeg(float degrees);

    void SetAngleRad(float radians);

    void SetRandomAngleDeg(const Vector2f& degrees);

    void SetRandomAngleRad(const Vector2f& radians);

    void SetRandomAngleDeg(float from, float to);

    void SetRandomAngleRad(float from, float to);

private:
    void generate(Particle* p);

    Vector2f    m_angle;
};


class LinearParticleEmitter : public ParticleEmitter
{
public:
    LinearParticleEmitter();

    const Vector2f& GetPointA() const;

    const Vector2f& GetPointB() const;

    float GetAngleDeg() const;

    float GetAngleRad() const;

    void SetPointA(const Vector2f& a);

    void SetPointB(const Vector2f& b);

    void SetSegment(const Vector2f& a, const Vector2f& b);

    void SetAngleDeg(float degrees);

    void SetAngleRad(float radians);

private:
    void generate(Particle* p);

    Vector2f    m_a;
    Vector2f    m_b;
    Vector2f    m_normal;
    float       m_angle;
};

}

#endif // PARTICLES_H
