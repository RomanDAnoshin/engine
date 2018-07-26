#ifndef EVENT_H
#define EVENT_H
#include <list>
#include <functional>

namespace engine
{
template <typename T>
class AbstractDelegate;

template<typename return_type, typename... arg_types>
class AbstractDelegate<return_type(arg_types...)>
{
public:
    virtual ~AbstractDelegate()
    {

    }

    virtual return_type Invoke(arg_types... args...) const = 0;
};

template <typename T>
class Delegate;

template <typename callee_type, typename return_type, typename... arg_types>
class Delegate<return_type (callee_type::*)(arg_types...)> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef return_type (callee_type::*func_type)(arg_types...);

public:
    Delegate(func_type func, callee_type* callee) :
        m_callee(callee),
        m_function(func)
    {

    }

    return_type Invoke(arg_types... args...) const
    {
        return (m_callee.*m_function)(args...);
    }

private:
    callee_type*    m_callee;
    func_type       m_function;
};

template <typename callee_type, typename return_type, typename... arg_types>
class Delegate<return_type (callee_type::*)(arg_types...) const> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef return_type (callee_type::*func_type)(arg_types...) const;

public:
    Delegate(func_type func, const callee_type* callee) :
        m_callee(callee),
        m_function(func)
    {

    }

    return_type Invoke(arg_types... args...) const
    {
        return (m_callee.*m_function)(args...);
    }

private:
    const callee_type*  m_callee;
    func_type           m_function;
};

template <typename return_type, typename... arg_types>
class Delegate<return_type (*)(arg_types...)> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef return_type (*func_type)(arg_types...);

public:
    Delegate(func_type func) :
        m_function(func)
    {

    }

    return_type Invoke(arg_types... args...) const
    {
        return (*m_function)(args...);
    }

private:
    func_type m_function;
};

template <typename return_type, typename... arg_types>
class Delegate<std::function<return_type(arg_types...)>> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef std::function<return_type(arg_types...)> func_type;

public:
    Delegate(const func_type& func) :
        m_function(func)
    {

    }

    return_type Invoke(arg_types... args...) const
    {
        return m_function(args...);
    }

private:
    func_type m_function;
};


template<typename... arg_types>
class Event
{
public:

    Event()
    {

    }

    void ConnectStdFunction(const std::function<void(arg_types...)>& func,
                            const std::string& name = std::string())
    {
        typedef std::function<void(arg_types...)> func_type;
        auto delegate = new Delegate<func_type>(func);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    void ConnectFreeFunction(void (*func)(arg_types...),
                            const std::string& name = std::string())
    {
        typedef void (*func_type)(arg_types...);
        auto delegate = new Delegate<func_type>(func);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    template <typename class_type>
    void ConnectMethod(void (class_type::*func)(arg_types...), class_type* obj,
                       const std::string& name = std::string())
    {
        typedef void (class_type::*func_type)(arg_types...);
        auto delegate = new Delegate<func_type>(func, obj);
        auto p = dynamic_cast<AbstractDelegate<void(arg_types...)>*>(delegate);
        m_delegates.push_back(std::make_pair(name, p));
    }

    template <typename class_type>
    void ConnectMethod(void (class_type::*func)(arg_types...) const, const class_type* obj,
                            const std::string& name = std::string())
    {
        typedef void (class_type::*func_type)(arg_types...) const;
        auto delegate = new Delegate<func_type>(func, obj);
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
        if (m_delegates.empty()) {
            return;
        }
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

    bool IsEmpty() const
    {
        return m_delegates.empty();
    }

private:
    std::list<std::pair<std::string, AbstractDelegate<void(arg_types...)>*>> m_delegates;
};

}

#endif // EVENT_H
