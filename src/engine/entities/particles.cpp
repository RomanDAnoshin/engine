#include "engine/entities/particles.h"
using namespace engine;

ParticleEmitter::ParticleEmitter():
    Entity(),
    Textured(),
    m_maxCount(0),
    m_timeToEmit(m_parameters.delayRange.x),
    m_running(true),
    m_dynamicColor(false),
    m_dynamicRadius(false)
{
    SetMaxParticleCount(10);
}

ParticleEmitter::~ParticleEmitter()
{
    for (Particle* p : m_alive) {
        delete p;
    }
    m_alive.clear();
    for (Particle* p : m_dead) {
        delete p;
    }
    m_dead.clear();
    m_maxCount = 0;
}

size_t ParticleEmitter::GetMaxParticleCount() const
{
    return m_maxCount;
}

size_t ParticleEmitter::GetAliveParticleCount() const
{
    return m_alive.size();
}

bool ParticleEmitter::IsRunning() const
{
    return m_running;
}

const ParticleParameters& ParticleEmitter::GetParameters()
{
    return m_parameters;
}

void ParticleEmitter::SetMaxParticleCount(int count)
{
    if (count < 0) {
        count = 0;
    }
    if (m_maxCount == count) {
        return;
    }
    if (m_maxCount < count) {
        for (size_t i = 0; i < count - m_maxCount; ++i) {
            m_dead.push_back(new Particle());
        }
    } else {
        int popCount = m_maxCount - count;
        while (popCount > 0 && m_dead.size() > 0) {
            popCount--;
            Particle* p = m_dead.back();
            delete p;
            m_dead.pop_back();
        }
        while (popCount > 0 && m_alive.size() > 0) {
            popCount--;
            Particle* p = m_alive.back();
            delete p;
            m_alive.pop_back();
        }
    }
    m_maxCount = count;
}

void ParticleEmitter::Play()
{
    m_running = true;
}

void ParticleEmitter::Stop()
{
    m_running = false;
}

void ParticleEmitter::SetParameters(const ParticleParameters& parameters)
{
    m_parameters = parameters;
    m_dynamicColor = m_parameters.startColorRange != m_parameters.finishColorRange;
    m_dynamicRadius = m_parameters.startRadiusRange != m_parameters.finishRadiusRange;
}

void ParticleEmitter::Update(const float dt)
{
    Entity::Update(dt);
    for (auto i = m_alive.begin(); i != m_alive.end(); ++i) {
        Particle* p = (*i);
        p->lifetime -= dt;
        if (p->lifetime <= 0) {
            m_dead.push_back(p);
            i = m_alive.erase(i);
            if (m_dynamicColor) {
                if (p->color != nullptr) {
                    delete[] p->color;
                    p->color = nullptr;
                }
            }
            if (m_dynamicRadius) {
                if (p->radius != nullptr) {
                    delete[] p->radius;
                    p->radius = nullptr;
                }
            }
            continue;
        }
        p->velocity += m_parameters.gravity * dt;
        p->position += p->velocity * dt;

        float ratio = p->lifetime / m_parameters.lifetimeRange.y;

        if (m_dynamicColor) {
            p->color[0] = lerp(p->color[2], p->color[1], ratio);
        }
        if (m_dynamicRadius) {
            p->radius[0] = p->radius[2] + (p->radius[1] - p->radius[2]) * ratio;
        }
    }
    if (!m_running) {
        return;
    }
    m_timeToEmit -= dt;
    while (m_timeToEmit <= 0 && !m_dead.empty()) {
        Particle* p = m_dead.back();
        m_dead.pop_back();

        p->position = Vector2f(0.f, 0.f);

        if (m_dynamicColor) {
            p->color = new Color[3];
            p->color[1] = randomColor(m_parameters.startColorRange.x,
                                      m_parameters.startColorRange.y);
            p->color[2] = randomColor(m_parameters.finishColorRange.x,
                                      m_parameters.finishColorRange.y);
            p->color[0] = p->color[1];
        } else {
            p->color = new Color[1];
            p->color[0] = randomColor(m_parameters.startColorRange.x,
                                      m_parameters.startColorRange.y);
        }

        if (m_dynamicRadius) {
            p->radius = new float[3];
            p->radius[1] = randomf(m_parameters.startRadiusRange.x,
                                   m_parameters.startRadiusRange.y);
            p->radius[2] = randomf(m_parameters.finishRadiusRange.x,
                                   m_parameters.finishRadiusRange.y);
            p->radius[0] = p->radius[1];
        } else {
            p->radius = new float[1];
            p->radius[0] = randomf(m_parameters.startRadiusRange.x,
                                   m_parameters.startRadiusRange.y);
        }

        p->lifetime = randomf(m_parameters.lifetimeRange.x,
                              m_parameters.lifetimeRange.y);

        generate(p);

        m_alive.push_back(p);
        m_timeToEmit += randomf(m_parameters.delayRange.x, m_parameters.delayRange.y);
    }
}

void ParticleEmitter::Render(Renderer& renderer)
{
    if (m_bitmap == nullptr) {
        return;
    }
    prepareRenderer(renderer);
    for (auto it = m_alive.begin(); it != m_alive.end(); ++it) {
        Particle* p = (*it);
        float r = p->radius[0];
        float r2 = r * 2;
        FloatRect dst(p->position.x - r, p->position.y - r, r2, r2);
        renderer.DrawBitmap(m_bitmap, m_source, dst, p->color[0]);
    }
}

PointParticleEmitter::PointParticleEmitter() :
    m_angle(Angle::FromDegrees(0.f), Angle::FromDegrees(360.f))
{

}

const Vector2<Angle>& PointParticleEmitter::GetAngle() const
{
    return m_angle;
}

void PointParticleEmitter::SetAngle(Angle angle)
{
    m_angle = Vector2<Angle>(angle, angle);
}

void PointParticleEmitter::SetRandomAngle(const Vector2<Angle>& angle)
{
    SetRandomAngle(angle.x, angle.y);
}

void PointParticleEmitter::SetRandomAngle(Angle from, Angle to)
{
    m_angle.x = from;
    m_angle.y = to;
    m_angle.Sort();
}


void PointParticleEmitter::generate(Particle* p)
{
    float angle = randomf(m_angle.x, m_angle.y);
    float vel = randomf(m_parameters.velocityRange.x,
                        m_parameters.velocityRange.y);
    p->velocity = Vector2f(std::cos(angle) * vel, std::sin(angle) * vel);
}

LinearParticleEmitter::LinearParticleEmitter() :
    m_a(10.f, 0.f),
    m_b(-10.f, 0.f),
    m_normal(0.f, -1.f),
    m_angle(Angle::FromDegrees(-90))
{

}

const Vector2f& LinearParticleEmitter::GetPointA() const
{
    return m_a;
}

const Vector2f& LinearParticleEmitter::GetPointB() const
{
    return m_b;
}

Angle LinearParticleEmitter::GetAngle() const
{
    return m_angle;
}

void LinearParticleEmitter::SetPointA(const Vector2f& a)
{
    m_a = a;
}

void LinearParticleEmitter::SetPointB(const Vector2f& b)
{
    m_b = b;
}

void LinearParticleEmitter::SetSegment(const Vector2f& a, const Vector2f& b)
{
    m_a = a;
    m_b = b;
}

void LinearParticleEmitter::SetAngle(Angle angle)
{
    if (m_angle == angle) {
        return;
    }
    m_angle = angle;
    m_normal = Vector2f(std::cos(m_angle), std::sin(m_angle));
}

void LinearParticleEmitter::generate(Particle* p)
{
    float r = randomf(0.f, 1.f);
    p->position += Vector2f(m_a.x + (m_b.x - m_a.x) * r,
                            m_a.y + (m_b.y - m_a.y) * r);
    float vel = randomf(m_parameters.velocityRange.x,
                        m_parameters.velocityRange.y);
    p->velocity = m_normal * vel;
}
