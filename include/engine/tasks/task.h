#ifndef TASK_H
#define TASK_H

#include "engine/common/event.h"

namespace engine
{

class Task
{
public:
    Task() :
        m_userData(nullptr), m_finished(false) { }

    virtual ~Task() = default;

    void* GetUserData() { return m_userData; }

    bool IsFinished() const { return m_finished; }

    void SetUserData(void* userData) { m_userData = userData; }

    virtual void Finish()
    {
        m_finished = true;
        m_eventFinished.Invoke();
    }

    Event<>& EventFinished() { return m_eventFinished; }

    virtual void Update(const float dt) = 0;

protected:
    void*   m_userData;
    bool    m_finished;

private:
    Event<> m_eventFinished;
};

}

#endif // TASK_H
