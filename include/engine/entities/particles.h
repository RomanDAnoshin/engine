#ifndef PARTICLES_H
#define PARTICLES_H

#include "engine/texture.h"
#include "entity.h"
#include <list>
#include <cmath>

namespace engine
{

struct ParticleParameters
{
    ParticleParameters() :
        startRadiusRange(10.f),
        finishRadiusRange(10.f),
        velocityRange(50.f),
        lifetimeRange(1.f),
        delayRange(0.1f)
    {

    }

    Vector2<Color>  startColorRange;
    Vector2<Color>  finishColorRange;
    Vector2f        startRadiusRange;
    Vector2f        finishRadiusRange;
    Vector2f        velocityRange;
    Vector2f        lifetimeRange;
    Vector2f        delayRange;
    Vector2f        gravity;
};

class ParticleEmitter : public Entity, public Textured
{
public:
    ParticleEmitter();

    virtual ~ParticleEmitter();

    size_t GetMaxParticleCount() const;

    size_t GetAliveParticleCount() const;

    bool IsRunning() const;

    const ParticleParameters& GetParameters();

    void SetMaxParticleCount(int count);

    void Play();

    void Stop();

    void SetParameters(const ParticleParameters& parameters);

    void Update(const float dt);

    void Render(Renderer& renderer);

protected:
    struct Particle
    {
        ~Particle() {
            if (color != nullptr) {
                delete[] color;
                color = nullptr;
            }
            if (radius != nullptr) {
                delete[] radius;
                radius = nullptr;
            }
        }
        Vector2f    position;
        Vector2f    velocity;
        Color*      color;
        float*      radius;
        float       lifetime;
    };

    float randomf(float from, float to) {
        return ((to - from) * ((float)std::rand() / RAND_MAX)) + from;
    }

    int randomi(int from, int to) {
        return from + (std::rand() % (to - from + 1));
    }

    Color randomColor(const Color& from, const Color& to) {
        return Color(randomi(from.r, to.r),
                     randomi(from.g, to.g),
                     randomi(from.b, to.b),
                     randomi(from.a, to.a));
    }

    virtual void generate(Particle* p) = 0;

    ParticleParameters      m_parameters;
    std::list<Particle*>    m_alive;
    std::list<Particle*>    m_dead;

    size_t          m_maxCount;
    float           m_timeToEmit;
    bool            m_running;
    bool            m_dynamicColor;
    bool            m_dynamicRadius;
};


class PointParticleEmitter : public ParticleEmitter
{
public:
    PointParticleEmitter();

    const Vector2<Angle>& GetAngle() const;

    void SetAngle(Angle angle);

    void SetRandomAngle(const Vector2<Angle>& angle);

    void SetRandomAngle(Angle from, Angle to);

private:
    void generate(Particle* p);

    Vector2<Angle>  m_angle;
};


class LinearParticleEmitter : public ParticleEmitter
{
public:
    LinearParticleEmitter();

    const Vector2f& GetPointA() const;

    const Vector2f& GetPointB() const;

    Angle GetAngle() const;

    void SetPointA(const Vector2f& a);

    void SetPointB(const Vector2f& b);

    void SetSegment(const Vector2f& a, const Vector2f& b);

    void SetAngle(Angle angle);

private:
    void generate(Particle* p);

    Vector2f    m_a;
    Vector2f    m_b;
    Vector2f    m_normal;
    Angle       m_angle;
};

}

#endif // PARTICLES_H
