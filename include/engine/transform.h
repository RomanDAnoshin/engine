#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "globals.h"
#include "tools/event.h"
#include <allegro5/allegro.h>

namespace engine
{

class Transform
{
public:
    Transform();

    Transform(const Vector2f& translate, const Vector2f& scale, float angle);

    Transform(float x, float y, float scaleX, float scaleY, float angle);

    void Build(const Vector2f& translate, const Vector2f& scale, float angle);

    void Build(float x, float y, float scaleX, float scaleY, float angle);

    void Compose(const Transform& other);

    void Translate(const Vector2f& translate);

    void Translate(float x, float y);

    void Scale(const Vector2f& scale);

    void Scale(float scaleX, float scaleY);

    void Rotate(float angle);

    void Reset();

private:
    float m[4][4];
};

class Transformable
{
public:
    Transformable();

    virtual ~Transformable() = 0;

    const Vector2f& GetPosition() const;

    const Vector2f& GetScale() const;

    float GetRotationDeg() const;

    float GetRotationRad() const;

    void SetPosition(const Vector2f& position);

    void SetPosition(float x, float y);

    void SetScale(const Vector2f& scale);

    void SetScale(float scaleX, float scaleY);

    void SetRotationDeg(float degrees);

    void SetRotationRad(float radians);

    Event<const Vector2f&>& EventPositionChanged();

    Event<const Vector2f&>& EventScaleChanged();

    Event<float>& EventRotationChanged();

protected:
    Vector2f    m_position;
    Vector2f    m_scale;
    float       m_rotation;
    Transform   m_transform;

private:
    void rebuildTransform();
    void positionChanged();
    void scaleChanged();
    void rotationChanged();

    Event<const Vector2f&>  m_positionChanged;
    Event<const Vector2f&>  m_scaleChanged;
    Event<float>            m_rotationChanged;
};

}

#endif // TRANSFORM_H
