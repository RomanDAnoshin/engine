#ifndef LERP_H
#define LERP_H

#include "property.h"

namespace engine
{

class AbstractLerp
{
public:
    AbstractLerp(float time) :
        m_fullTime(time), m_currentTime(time), m_isFinished(false) { }

    virtual void Step(const float dt) = 0;
    bool IsFinished() const { return m_isFinished; }

protected:
    float   m_fullTime;
    float   m_currentTime;
    bool    m_isFinished;
};

template<class arg_type, class value_type>
class Lerp : public AbstractLerp
{
public:
    Lerp(const AbstractProperty<arg_type>* property, value_type finishValue, float time) :
        AbstractLerp(time),
        m_startValue(property->GetValue()),
        m_finishValue(finishValue),
        m_property(property->Clone())
    {

    }

    virtual ~Lerp() { delete m_property; }

    void Step(const float dt)
    {
        if (m_isFinished) {
            return;
        }
        if ((m_currentTime -= dt) < 0) {
            m_isFinished = true;
            return;
        }
        float percent = m_currentTime / m_fullTime;
        value_type value = m_startValue * percent + m_finishValue * (1.f - percent);
        m_property->SetValue(value);
    }

private:
    value_type                  m_startValue;
    value_type                  m_finishValue;
    AbstractProperty<arg_type>* m_property;
};

}

#endif // LERP_H
