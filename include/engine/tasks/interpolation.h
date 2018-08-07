#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "timer.h"
#include "engine/common/math.h"
#include "engine/common/property.h"
#include <type_traits>

namespace engine
{

template<typename arg_type>
class Lerp : public Timer
{
    using value_type = typename std::decay<arg_type>::type;
public:
    Lerp(const Property<arg_type>& property, arg_type startValue, arg_type finishValue, float time) :
        Timer(time),
        m_property(property),
        m_startValue(startValue),
        m_finishValue(finishValue)
    {

    }

    Lerp(const Property<arg_type>& property, arg_type finishValue, float time) :
        Lerp(property, property.GetValue(), finishValue, time) { }

    void Update(const float dt)
    {
        if (m_finished) {
            return;
        }
        if ((m_currentTime += dt) > m_totalTime) {
            Finish();
        }
        float ratio = m_currentTime / m_totalTime;
        value_type value = math::lerp(m_startValue, m_finishValue, ratio);
        m_property.SetValue(value);
    }

protected:
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
