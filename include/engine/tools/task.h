#ifndef TASK_H
#define TASK_H

#include "event.h"

namespace engine
{

class Task
{
public:
    Task() : m_finished(false) { }

    virtual ~Task() { }

    virtual void Update(const float dt) = 0;

    bool IsFinished() const { return m_finished; }

    virtual void Finish()
    {
        m_finished = true;
        m_eventFinished.Invoke();
    }

    Event<>& EventFinished() { return m_eventFinished; }

protected:
    bool m_finished;

private:
    Event<> m_eventFinished;
};

}

#endif // TASK_H
