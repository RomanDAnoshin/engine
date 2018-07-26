#include "entities/particles.h"
using namespace engine;

ParticleEmitter::ParticleEmitter():
    Entity(),
    Textured(),
    m_dynColor(false),
    m_dynRadius(false),
    m_startRadius(10.f, 10.f),
    m_finishRadius(10.f, 10.f),
    m_velocity(50.f, 50.f),
    m_lifetime(1.f, 1.f),
    m_period(0.1f, 0.1f),
    m_timeToEmit(0.1f),
    m_count(10),
    m_deadCount(0),
    m_looped(true),
    m_stopped(false)
{

}

ParticleEmitter::~ParticleEmitter()
{
    for (Particle* p : m_alive)
        delete p;
    m_alive.clear();
    for (Particle* p : m_dead)
        delete p;
    m_dead.clear();
}

const Vector2f& ParticleEmitter::GetForce() const
{
    return m_force;
}

const Vector2<Color>& ParticleEmitter::GetStartColor() const
{
    return m_startColor;
}

const Vector2<Color>& ParticleEmitter::GetFinishColor() const
{
    if (m_dynColor == true)
        return m_finishColor;
    else
        return m_startColor;
}

const Vector2f& ParticleEmitter::GetStartRadius() const
{
    return m_startRadius;
}

const Vector2f& ParticleEmitter::GetFinishRadius() const
{
    if (m_dynRadius == true)
        return m_finishRadius;
    else
        return m_startRadius;
}

const Vector2f& ParticleEmitter::GetVelocity() const
{
    return m_velocity;
}

const Vector2f& ParticleEmitter::GetLifetime() const
{
    return m_lifetime;
}

const Vector2f& ParticleEmitter::GetPeriod() const
{
    return m_period;
}

size_t ParticleEmitter::GetParticleCount() const
{
    return m_count;
}

bool ParticleEmitter::IsStopped() const
{
    return m_stopped;
}

bool ParticleEmitter::IsLooped() const
{
    return m_looped;
}

void ParticleEmitter::SetForce(const Vector2f& force)
{
    m_force = force;
}

void ParticleEmitter::SetForce(float forceX, float forceY)
{
    m_force = Vector2f(forceX, forceY);
}

void ParticleEmitter::SetColor(const Color& color)
{
    m_startColor = Vector2<Color>(color, color);
    m_dynColor = false;
}

void ParticleEmitter::SetRandomColor(const Vector2<Color>& color)
{
    m_startColor = color;
    m_dynColor = false;
}

void ParticleEmitter::SetRandomColor(const Color &from, const Color &to)
{
    m_startColor = Vector2<Color>(from, to);
    m_dynColor = false;
}

void ParticleEmitter::SetRadius(float radius)
{
    m_startRadius = Vector2f(radius, radius);
    m_dynRadius = false;
}

void ParticleEmitter::SetRandomRadius(const Vector2f& radius)
{
    m_startRadius = radius;
    m_startRadius.Sort();
    m_dynRadius = false;
}

void ParticleEmitter::SetRandomRadius(float from, float to)
{
    m_startRadius = Vector2f(from, to);
    m_startRadius.Sort();
    m_dynRadius = false;
}

void ParticleEmitter::SetDynamicColor(const Color& start, const Color& finish)
{
    m_startColor = Vector2<Color>(start, start);
    m_finishColor = Vector2<Color>(finish, finish);
    m_dynColor = true;
}

void ParticleEmitter::SetDynamicRandomColor(const Vector2<Color>& start, const Vector2<Color>& finish)
{
    m_startColor = start;
    m_finishColor = finish;
    m_dynColor = true;
}

void ParticleEmitter::SetDynamicRadius(float start, float finish)
{
    m_startRadius = Vector2f(start, start);
    m_finishRadius = Vector2f(finish, finish);
    m_dynRadius = true;
}

void ParticleEmitter::SetDynamicRandomRadius(const Vector2f& start, const Vector2f& finish)
{
    m_startRadius = start;
    m_startRadius.Sort();
    m_finishRadius = finish;
    m_finishRadius.Sort();
    m_dynRadius = true;
}

void ParticleEmitter::SetVelocity(float velocity)
{
    m_velocity = Vector2f(velocity, velocity);
}

void ParticleEmitter::SetRandomVelocity(const Vector2f& velocity)
{
    m_velocity = velocity;
    m_velocity.Sort();
}

void ParticleEmitter::SetRandomVelocity(float from, float to)
{
    m_velocity = Vector2f(from, to);
    m_velocity.Sort();
}

void ParticleEmitter::SetLifetime(float lifeTime)
{
    m_lifetime = Vector2f(lifeTime, lifeTime);
}

void ParticleEmitter::SetRandomLifetime(const Vector2f& lifeTime)
{
    m_lifetime = lifeTime;
    m_lifetime.Sort();
}

void ParticleEmitter::SetRandomLifetime(float from, float to)
{
    m_lifetime = Vector2f(from, to);
    m_lifetime.Sort();
}

void ParticleEmitter::SetPeriod(float period)
{
    m_period = Vector2f(period, period);
    m_timeToEmit = period;
}

void ParticleEmitter::SetRandomPeriod(const Vector2f& period)
{
    m_period = period;
    m_period.Sort();
    m_timeToEmit = randomf(m_period.x, m_period.y);
}

void ParticleEmitter::SetRandomPeriod(float from, float to)
{
    m_period = Vector2f(from, to);
    m_period.Sort();
    m_timeToEmit = randomf(m_period.x, m_period.y);
}

void ParticleEmitter::SetParticleCount(size_t count)
{
    for (Particle* p : m_alive)
        delete p;
    m_alive.clear();
    for (Particle* p : m_dead)
        delete p;
    m_dead.clear();
    for (size_t i = 0; i < count; ++i) {
        m_dead.push_back(new Particle());
    }
    m_count = count;
    m_timeToEmit = randomf(m_period.x, m_period.y);
}

void ParticleEmitter::SetStopped(bool stopped)
{
    m_stopped = stopped;
}

void ParticleEmitter::SetLooped(bool looped)
{
    m_looped = looped;
}

void ParticleEmitter::Update(const float dt)
{
    for (auto i = m_alive.begin(); i != m_alive.end(); ++i) {
        Particle* p = (*i);
        p->lifetime -= dt;
        if (p->lifetime <= 0) {
            if (!m_looped && !m_stopped)
                m_deadCount+=1;
            m_dead.push_back(p);
            i = m_alive.erase(i);
            continue;
        }
        p->velocity += m_force * dt;
        p->position += p->velocity * dt;

        float ratio = p->lifetime / m_lifetime.y;

        if (m_dynColor) {
            p->color.r = p->colorRange.y.r - (p->colorRange.y.r - p->colorRange.x.r) * ratio;
            p->color.g = p->colorRange.y.g - (p->colorRange.y.g - p->colorRange.x.g) * ratio;
            p->color.b = p->colorRange.y.b - (p->colorRange.y.b - p->colorRange.x.b) * ratio;
            p->color.a = p->colorRange.y.a - (p->colorRange.y.a - p->colorRange.x.a) * ratio;
        }
        if (m_dynRadius)
            p->radius = p->radiusRange.y - (p->radiusRange.y - p->radiusRange.x) * ratio;
    }
    m_timeToEmit -= dt;
    if (!m_looped && (m_deadCount >= m_count)) {
        m_stopped = true;
        m_deadCount = 0;
    }
    while (m_timeToEmit <= 0 && !m_dead.empty() && !m_stopped) {
        Particle* p = m_dead.back();
        m_dead.pop_back();

        p->position = Vector2f(0.f, 0.f);

        p->colorRange.x = Color(randomi(m_startColor.x.r, m_startColor.y.r),
                                randomi(m_startColor.x.g, m_startColor.y.g),
                                randomi(m_startColor.x.b, m_startColor.y.b),
                                randomi(m_startColor.x.a, m_startColor.y.a));
        p->colorRange.y = Color(randomi(m_finishColor.x.r, m_finishColor.y.r),
                                randomi(m_finishColor.x.g, m_finishColor.y.g),
                                randomi(m_finishColor.x.b, m_finishColor.y.b),
                                randomi(m_finishColor.x.a, m_finishColor.y.a));
        p->color = p->colorRange.x;

        p->radiusRange.x = randomf(m_startRadius.x, m_startRadius.y);
        p->radiusRange.y = randomf(m_finishRadius.x, m_finishRadius.y);
        p->radius = p->radiusRange.x;

        p->lifetime = randomf(m_lifetime.x, m_lifetime.y);

        generate(p);

        m_alive.push_back(p);
        m_timeToEmit += randomf(m_period.x, m_period.y);
    }
}

void ParticleEmitter::Render(Renderer& renderer)
{
    if (m_bitmap == nullptr) {
        return;
    }
    prepareRenderer(renderer);
    Transform transform = renderer.GetTransform();
    for (Particle* i : m_alive) {
        Transform tr(i->position, Vector2f(1.f, 1.f), 0.f);
        tr.Compose(transform);
        renderer.SetTransform(tr);
        float r = i->radius;
        float r2 = r * 2;
        FloatRect dst({-r, -r}, {r2, r2});
        renderer.DrawBitmap(m_bitmap, m_source, dst, i->color);
    }
}

PointParticleEmitter::PointParticleEmitter() :
    m_angle(0.f, 360.f * 0.0174532925f)
{

}

Vector2f PointParticleEmitter::GetAngleDeg() const
{
    return m_angle * 57.2957795f;
}

const Vector2f& PointParticleEmitter::GetAngleRad() const
{
    return m_angle;
}

void PointParticleEmitter::SetAngleDeg(float degrees)
{
    m_angle = Vector2f(degrees, degrees) * 0.0174532925f;
}

void PointParticleEmitter::SetAngleRad(float radians)
{
    m_angle = Vector2f(radians, radians);
}

void PointParticleEmitter::SetRandomAngleDeg(const Vector2f& degrees)
{
    m_angle = degrees * 0.0174532925f;
    m_angle.Sort();
}

void PointParticleEmitter::SetRandomAngleRad(const Vector2f& radians)
{
    m_angle = radians;
    m_angle.Sort();
}

void PointParticleEmitter::SetRandomAngleDeg(float from, float to)
{
    m_angle = Vector2f(from, to) * 0.0174532925f;
    m_angle.Sort();
}

void PointParticleEmitter::SetRandomAngleRad(float from, float to)
{
    m_angle = Vector2f(from, to);
    m_angle.Sort();
}

void PointParticleEmitter::generate(Particle* p)
{
    float angle = randomf(m_angle.x, m_angle.y);
    float vel = randomf(m_velocity.x, m_velocity.y);
    p->velocity = Vector2f(std::cos(angle) * vel, std::sin(angle) * vel);
}

LinearParticleEmitter::LinearParticleEmitter() :
    m_a(10.f, 0.f),
    m_b(-10.f, 0.f),
    m_normal(0.f, -1.f),
    m_angle(-90.f * 0.0174532925f)
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

float LinearParticleEmitter::GetAngleDeg() const
{
    return m_angle * 57.2957795f;
}

float LinearParticleEmitter::GetAngleRad() const
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

void LinearParticleEmitter::SetAngleDeg(float degrees)
{
    float radians = degrees * 0.0174532925f;
    if (m_angle == radians)
        return;
    m_angle = degrees * 0.0174532925f;
    m_normal = Vector2f(std::cos(m_angle), std::sin(m_angle));
}

void LinearParticleEmitter::SetAngleRad(float radians)
{
    if (m_angle == radians)
        return;
    m_angle = radians;
    m_normal = Vector2f(std::cos(m_angle), std::sin(m_angle));
}

void LinearParticleEmitter::generate(Particle* p)
{
    float r = randomf(0.f, 1.f);
    p->position += Vector2f(m_a.x + (m_b.x - m_a.x) * r,
                            m_a.y + (m_b.y - m_a.y) * r);
    float vel = randomf(m_velocity.x, m_velocity.y);
    p->velocity = m_normal * vel;
}
