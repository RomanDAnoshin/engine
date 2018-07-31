#ifndef TASK_H
#define TASK_H

namespace engine
{

class Task
{
public:
    Task() : m_finished(false) { }
    virtual ~Task() { }
    virtual void Update(const float dt) = 0;
    bool IsFinished() const { return m_finished; }
protected:
    bool m_finished;
};

}

#endif // TASK_H
