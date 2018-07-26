#ifndef OBJECT_H
#define OBJECT_H

#include "renderer.h"
#include <string>
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

    static Object* GetObject(const std::string& name);

protected:
    Container*  m_container;
    std::string m_name;
    int         m_order;

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
