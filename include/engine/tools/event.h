#ifndef EVENT_H
#define EVENT_H

#include "delegate.h"
#include <list>

namespace engine
{

template <class... arg_types>
class Event
{
public:
    Event() { }

    void ConnectStdFunction(const std::function<void(arg_types...)>& func,
                            const std::string& name = std::string())
    {
        typedef std::function<void(arg_types...)> function_type;
        auto delegate = new Delegate<function_type>(func);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    void ConnectFreeFunction(void (*func)(arg_types...),
                            const std::string& name = std::string())
    {
        typedef void (*function_type)(arg_types...);
        auto delegate = new Delegate<function_type>(func);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    template <class class_type>
    void ConnectMethod(void (class_type::*func)(arg_types...), class_type* obj,
                       const std::string& name = std::string())
    {
        typedef void (class_type::*function_type)(arg_types...);
        auto delegate = new Delegate<function_type>(func, obj);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    template <class class_type>
    void ConnectMethod(void (class_type::*func)(arg_types...) const, const class_type* obj,
                            const std::string& name = std::string())
    {
        typedef void (class_type::*function_type)(arg_types...) const;
        auto delegate = new Delegate<function_type>(func, obj);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    void Disconnect(const std::string& name)
    {
        for (auto i = m_delegates.begin(); i != m_delegates.end(); ++i) {
            if ((*i).first == name) {
                delete (*i).second;
                i = m_delegates.erase(i);
            }
        }
    }

    void Invoke(arg_types... args...) const
    {
        for (auto i : m_delegates) {
            i.second->Invoke(args...);
        }
    }

    void Clear()
    {
        for (auto i : m_delegates) {
            delete i.second;
        }
        m_delegates.clear();
    }

    bool IsEmpty() const { return m_delegates.empty(); }

private:
    std::list<std::pair<std::string, AbstractDelegate<void(arg_types...)>*>> m_delegates;
};

}

#endif // EVENT_H
