#ifndef OBJECT_H
#define OBJECT_H

#include "renderer.h"
#include "tools/lerp.h"
#include <string>
#include <vector>
#include <map>

namespace engine
{

class Container;

class Object
{
public:
    Object();

    virtual ~Object() = 0;

    Container* GetContainer() const;

    std::string GetName() const;

    int GetOrder() const;

    void SetName(const std::string& name);

    template <class arg_type, class class_type, class value_type>
    void LerpProperty(arg_type(class_type::*getter)(void) const, void(class_type::*setter)(arg_type),
              value_type finishValue, float time)
    {
        class_type* object = dynamic_cast<class_type*>(this);
        if (object == nullptr) {
            throw std::invalid_argument("Cannot cast this to class_type\n");
        }
        Property<arg_type, class_type> property(getter, setter, object);
        auto lerp = new Lerp<arg_type, value_type>(property.ToAbstractProperty(), finishValue, time);
        m_lerps.push_back(dynamic_cast<AbstractLerp*>(lerp));
    }

    virtual void Update(const float dt);

    static Object* GetObject(const std::string& name);

protected:
    Container*  m_container;
    std::string m_name;
    int         m_order;

    std::list<AbstractLerp*>    m_lerps;

private:
    static std::map<std::string, Object*> m_mappedObjects;
    friend class Container;
};

class Container
{
public:
    Container();

    virtual ~Container();

    const std::vector<Object*>& GetObjects() const;

    void Clear(bool free = false);

    void AddObject(Object* object, unsigned order = -1);

    void RemoveObject(Object* object, bool free = false);

    void ChangeOrder(Object* object, unsigned order);

protected:
    std::vector<Object*>    m_objects;
};

}

#endif // OBJECT_H
