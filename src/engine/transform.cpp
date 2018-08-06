#include "engine/transform.h"
using namespace engine;

Transform::Transform()
{
    Reset();
}

Transform::Transform(const Vector2f& translate, const Vector2f& scale, float angle)
{
    Build(translate, scale, angle);
}

Transform::Transform(float x, float y, float scaleX, float scaleY, float angle)
{
    Build(x, y, scaleX, scaleY, angle);
}

void Transform::Build(const Vector2f& translate, const Vector2f& scale, float angle)
{
    Build(translate.x, translate.y, scale.x, scale.y, angle);
}

void Transform::Build(float x, float y, float scaleX, float scaleY, float angle)
{
    ALLEGRO_TRANSFORM* tr = reinterpret_cast<ALLEGRO_TRANSFORM*>(this);
    al_build_transform(tr, x, y, scaleX, scaleY, angle);
}

void Transform::Compose(const Transform& other)
{
    ALLEGRO_TRANSFORM* tr1 = reinterpret_cast<ALLEGRO_TRANSFORM*>(this);
    const ALLEGRO_TRANSFORM* tr2 = reinterpret_cast<const ALLEGRO_TRANSFORM*>(&other);
    al_compose_transform(tr1, tr2);
}

void Transform::Translate(const Vector2f& translate)
{
    Translate(translate.x, translate.y);
}

void Transform::Translate(float x, float y)
{
    ALLEGRO_TRANSFORM* tr = reinterpret_cast<ALLEGRO_TRANSFORM*>(this);
    al_translate_transform(tr, x, y);
}

void Transform::Scale(const Vector2f& scale)
{
    Scale(scale.x, scale.y);
}

void Transform::Scale(float scaleX, float scaleY)
{
    ALLEGRO_TRANSFORM* tr = reinterpret_cast<ALLEGRO_TRANSFORM*>(this);
    al_scale_transform(tr, scaleX, scaleY);
}

void Transform::Rotate(float angle)
{
    ALLEGRO_TRANSFORM* tr = reinterpret_cast<ALLEGRO_TRANSFORM*>(this);
    al_rotate_transform(tr, angle);
}

void Transform::Reset()
{
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;

    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = 0;

    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = 0;

    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}

Transformable::Transformable() :
    m_position(0.f, 0.f),
    m_scale(1.f, 1.f),
    m_rotation(0.f)
{

}

Transformable::~Transformable()
{

}

const Vector2f& Transformable::GetPosition() const
{
    return m_position;
}

const Vector2f& Transformable::GetScale() const
{
    return m_scale;
}

Angle Transformable::GetRotation() const
{
    return radiansToDegrees(m_rotation);
}

void Transformable::SetPosition(const Vector2f& position)
{
    SetPosition(position.x, position.y);
}

void Transformable::SetPosition(float x, float y)
{
    if (m_position.x == x && m_position.y == y) {
        return;
    }
    m_position.x = x;
    m_position.y = y;
    positionChanged();
}

void Transformable::SetScale(const Vector2f &scale)
{
    SetScale(scale.x, scale.y);
}

void Transformable::SetScale(float scaleX, float scaleY)
{
    if (m_scale.x == scaleX && m_scale.y == scaleY) {
        return;
    }
    m_position.x = scaleX;
    m_position.y = scaleY;
    scaleChanged();
}

void Transformable::SetRotation(Angle rotation)
{
    if (m_rotation == rotation) {
        return;
    }
    m_rotation = rotation;
    rotationChanged();
}

Event<const Vector2f&>& Transformable::EventPositionChanged()
{
    return m_positionChanged;
}

Event<const Vector2f&>& Transformable::EventScaleChanged()
{
    return m_scaleChanged;
}

Event<Angle>& Transformable::EventRotationChanged()
{
    return m_rotationChanged;
}

void Transformable::positionChanged()
{
    m_positionChanged.Invoke(m_position);
}

void Transformable::scaleChanged()
{
    m_scaleChanged.Invoke(m_scale);
}

void Transformable::rotationChanged()
{
    m_rotationChanged.Invoke(m_rotation);
}
