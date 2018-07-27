#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>

namespace engine
{

template <class T>
class AbstractDelegate;

template<class return_type, class... arg_types>
class AbstractDelegate<return_type(arg_types...)>
{
public:
    virtual ~AbstractDelegate() { }

    virtual return_type Invoke(arg_types... args...) const = 0;
};

template <class T>
class Delegate;

template <class class_type, class return_type, class... arg_types>
class Delegate<return_type (class_type::*)(arg_types...)> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef return_type (class_type::*function_type)(arg_types...);

public:
    Delegate(function_type function, class_type* object) :
        m_object(object), m_function(function) { }

    return_type Invoke(arg_types... args...) const { return (m_object->*m_function)(args...); }

private:
    class_type*     m_object;
    function_type   m_function;
};

template <class class_type, class return_type, class... arg_types>
class Delegate<return_type (class_type::*)(arg_types...) const> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef return_type (class_type::*function_type)(arg_types...) const;

public:
    Delegate(function_type function, const class_type* object) :
        m_object(object), m_function(function) { }

    return_type Invoke(arg_types... args...) const { return (m_object->*m_function)(args...); }

private:
    const class_type*   m_object;
    function_type       m_function;
};

template <class return_type, class... arg_types>
class Delegate<return_type (*)(arg_types...)> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef return_type (*function_type)(arg_types...);

public:
    Delegate(function_type func) : m_function(func) { }

    return_type Invoke(arg_types... args...) const { return (*m_function)(args...); }

private:
    function_type m_function;
};

template <class return_type, class... arg_types>
class Delegate<std::function<return_type(arg_types...)>> :
    public AbstractDelegate<return_type(arg_types...)>
{
    typedef std::function<return_type(arg_types...)> function_type;

public:
    Delegate(const function_type& func) : m_function(func) { }

    return_type Invoke(arg_types... args...) const { return m_function(args...); }

private:
    function_type m_function;
};

}

#endif // DELEGATE_H
