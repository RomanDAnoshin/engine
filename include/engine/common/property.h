#ifndef PROPERTY_H
#define PROPERTY_H

namespace engine
{

template <typename return_type>
class AbstractGetter
{
public:
    virtual ~AbstractGetter() = default;
    virtual AbstractGetter<return_type>* Clone() const = 0;
    virtual return_type Get() const = 0;
};

template <typename class_type, typename return_type>
class Getter : public AbstractGetter<return_type>
{
    typedef return_type(class_type::*getter_type)() const;
public:
    Getter(getter_type function, const class_type* object) :
        m_function(function), m_object(object) { }

    virtual AbstractGetter<return_type>* Clone() const {
        auto getter = new Getter<class_type, return_type>(m_function, m_object);
        return dynamic_cast<AbstractGetter<return_type>*>(getter);
    }

    virtual return_type Get() const { return (m_object->*m_function)(); }

private:
    const class_type*   m_object;
    getter_type         m_function;
};

template <typename arg_type>
class AbstractSetter
{
public:
    virtual ~AbstractSetter() = default;
    virtual AbstractSetter<arg_type>* Clone() const = 0;
    virtual void Set(arg_type args) const = 0;
};

template <typename class_type, typename arg_type>
class Setter : public AbstractSetter<arg_type>
{
    typedef void(class_type::*setter_type)(arg_type);
public:
    Setter(setter_type function, class_type* object) :
        m_function(function), m_object(object) { }

    virtual AbstractSetter<arg_type>* Clone() const {
        auto setter = new Setter<class_type, arg_type>(m_function, m_object);
        return dynamic_cast<AbstractSetter<arg_type>*>(setter);
    }

    virtual void Set(arg_type value) const { (m_object->*m_function)(value); }

private:
    class_type*   m_object;
    setter_type   m_function;
};

template <typename T>
class Property
{
public:
    Property(const AbstractGetter<T>* getter, const AbstractSetter<T>* setter) :
        m_getter(getter->Clone()), m_setter(m_setter->Clone()) { }

    template <typename class_type>
    Property(T(class_type::*getter)(void) const, void(class_type::*setter)(T), class_type* object)
    {
        m_getter = new Getter<class_type, T>(getter, object);
        m_setter = new Setter<class_type, T>(setter, object);
    }

    Property(const Property<T>& other)  :
        m_getter(other.m_getter->Clone()), m_setter(other.m_setter->Clone()) { }

    virtual ~Property() {
        delete m_getter;
        delete m_setter;
    }

    T GetValue() const { return m_getter->Get(); }
    void SetValue(T value) const { m_setter->Set(value); }

private:
    AbstractGetter<T>*   m_getter;
    AbstractSetter<T>*   m_setter;
};

}

#endif // PROPERTY_H
