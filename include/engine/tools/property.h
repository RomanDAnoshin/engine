#ifndef PROPERTY_H
#define PROPERTY_H

namespace engine
{

template <class arg_type>
class AbstractProperty
{
public:
    virtual ~AbstractProperty() { }
    virtual AbstractProperty<arg_type>* Clone() const = 0;
    virtual arg_type GetValue() const = 0;
    virtual void SetValue(arg_type arg) const = 0;
};

template <class arg_type, class class_type>
class Property : public AbstractProperty<arg_type>
{
    typedef arg_type(class_type::*getter_type)(void) const;
    typedef void(class_type::*setter_type)(arg_type);

public:
    Property(getter_type getter, setter_type setter, class_type* object) :
        m_getter(getter), m_setter(setter), m_object(object) { }

    Property(const Property& property) :
        m_getter(property.m_getter), m_setter(property.m_setter), m_object(property.m_object) { }

    AbstractProperty<arg_type>* ToAbstractProperty() {
        return dynamic_cast<AbstractProperty<arg_type>*>(this);
    }

    virtual AbstractProperty<arg_type>* Clone() const {
        auto property = new Property<arg_type, class_type>(m_getter, m_setter, m_object);
        return property->ToAbstractProperty();
    }

    virtual arg_type GetValue() const { return (m_object->*m_getter)(); }

    virtual void SetValue(arg_type value) const { (m_object->*m_setter)(value); }

private:
    getter_type m_getter;
    setter_type m_setter;
    class_type* m_object;
};

}

#endif // PROPERTY_H
