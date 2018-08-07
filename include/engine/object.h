#ifndef OBJECT_H
#define OBJECT_H

#include "renderer.h"
#include "tasks/task.h"
#include "common/property.h"
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

    const std::string& GetName() const;

    int GetOrder() const;

    void SetName(const std::string& name);

    template <typename arg_type, typename class_type>
    Property<arg_type> GetProperty(arg_type(class_type::*getter)(void) const,
                                   void(class_type::*setter)(arg_type))
    {
        class_type* object = dynamic_cast<class_type*>(this);
        if (object == nullptr) {
            throw std::invalid_argument("Wrong class type\n");
        }
        return Property<arg_type>(getter, setter, object);
    }

    void AddTask(Task* task);

    const std::list<Task*>& GetTasks() const;

    void ClearTasks();

    virtual void Update(const float dt);

    static Object* GetObject(const std::string& name);

protected:
    Container*  m_container;
    std::string m_name;
    int         m_order;

    std::list<Task*>    m_tasks;

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

    void Clear();

    void AddObject(Object* object, unsigned order = -1);

    void RemoveObject(Object* object);

    void ChangeOrder(Object* object, unsigned order);

protected:
    std::vector<Object*>    m_objects;
};

}

#endif // OBJECT_H
