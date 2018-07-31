#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "property.h"
#include "task.h"
#include <type_traits>

namespace engine
{

template<typename arg_type>
class Lerp : public Task
{
    using value_type = typename std::decay<arg_type>::type;
public:
    Lerp(const Property<arg_type>& property, arg_type startValue, arg_type finishValue, float time) :
        Task(),
        m_property(property),
        m_startValue(startValue),
        m_finishValue(finishValue),
        m_totalTime(time),
        m_currentTime(time)
    {

    }

    Lerp(const Property<arg_type>& property, arg_type startValue, float time) :
        Lerp(property, startValue, property.GetValue(), time) { }

    virtual ~Lerp() { }

    virtual void Update(const float dt)
    {
        if (m_finished) {
            return;
        }
        if ((m_currentTime -= dt) < 0) {
            m_finished = true;
            return;
        }
        float percent = m_currentTime / m_totalTime;
        value_type value = m_startValue * percent + m_finishValue * (1.f - percent);
        m_property.SetValue(value);
    }

protected:
    float               m_totalTime;
    float               m_currentTime;
    value_type          m_startValue;
    value_type          m_finishValue;
    Property<arg_type>  m_property;
};

template <typename arg_type, typename value_type>
inline Lerp<arg_type>* make_lerp(const Property<arg_type>& property, value_type startValue, value_type finishValue, float time)
{
    return new Lerp<arg_type>(property, startValue, finishValue, time);
}

template <typename arg_type, typename value_type>
inline Lerp<arg_type>* make_lerp(const Property<arg_type>& property, value_type finishValue, float time)
{
    return new Lerp<arg_type>(property, finishValue, time);
}

}

#endif // INTERPOLATION_H
