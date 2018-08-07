#ifndef TIMER_H
#define TIMER_H

#include "task.h"

namespace engine
{

class Timer : public Task
{
public:
    Timer(float time) :
        Task(),
        m_totalTime(time),
        m_currentTime(0.f)
    {

    }

    virtual void Update(const float dt)
    {
        if (m_finished) {
            return;
        }
        if ((m_currentTime += dt) > m_totalTime) {
            Finish();
        }
    }

protected:
    float   m_totalTime;
    float   m_currentTime;
};

}

#endif // TIMER_H
