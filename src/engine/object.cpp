#include "engine/object.h"
using namespace engine;

namespace engine
{
std::map<std::string, Object*> Object::m_mappedObjects;
}

Object::Object() :
    m_container(nullptr),
    m_order(-1)
{

}

Object::~Object()
{
    SetName(std::string());
    if (m_container != nullptr) {
        m_container->RemoveObject(this);
    }
    for (Task* task : m_tasks) {
        delete task;
    }
    m_tasks.clear();
}

Container* Object::GetContainer() const
{
    return m_container;
}

const std::string& Object::GetName() const
{
    return m_name;
}

void Object::SetName(const std::string& name)
{
    if (m_name == name) {
        return;
    }
    if (!name.empty()) {
        auto result = m_mappedObjects.insert(std::make_pair(name, this));
        if (result.second == false) {
            throw std::invalid_argument("Object with name \"" + name + "\" already exists\n");
        }
    }
    if (!m_name.empty()) {
        m_mappedObjects.erase(m_name);
    }
    m_name = name;
}

void Object::AddTask(Task* task)
{
    m_tasks.push_back(task);
}

const std::list<Task*>& Object::GetTasks() const
{
    return m_tasks;
}

void Object::Update(const float dt)
{
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
        auto task = *it;
        if (task->IsFinished()) {
            delete task;
            it = m_tasks.erase(it);
            continue;
        }
        task->Update(dt);
    }
}

int Object::GetOrder() const
{
    return m_order;
}

Object* Object::GetObject(const std::string& name)
{
    auto it = m_mappedObjects.find(name);
    if (it == m_mappedObjects.end()) {
        return nullptr;
    } else {
        return (*it).second;
    }
}

Container::Container()
{

}

Container::~Container()
{
    Clear();
}

const std::vector<Object*>&Container::GetObjects() const
{
    return m_objects;
}

void Container::Clear(bool free)
{
    for (auto i: m_objects) {
        RemoveObject(i, free);
    }
}

void Container::AddObject(Object* object, unsigned order)
{
    if (object == nullptr) {
        throw std::invalid_argument("Object is nullptr\n");
    }

    if (dynamic_cast<Container*>(object) == this) {
        throw std::invalid_argument("Can not add container to itself\n");
    }

    auto parent = object->m_container;
    if (parent == nullptr) {
        if (order >= m_objects.size()) {
            object->m_order = m_objects.size();
            m_objects.push_back(object);
        } else {
            object->m_order = order;
            m_objects.insert(m_objects.begin() + order, object);
        }
        object->m_container = this;
        return;
    }
    if (parent == this) {
        ChangeOrder(object, order);
    } else {
        parent->RemoveObject(object, false);
        AddObject(object, order);
    }
}

void Container::RemoveObject(Object* object, bool free)
{
    if (object == nullptr) {
        throw std::invalid_argument("Object is nullptr\n");
    }
    if (object->m_container != this) {
        throw std::invalid_argument("Does not contain object\n");
    }
    m_objects.erase(m_objects.begin() + object->m_order);
    for (int i = object->m_order; i != (int)m_objects.size(); ++i) {
        m_objects[i]->m_order = i;
    }
    if (free == true) {
        delete object;
    } else {
        object->m_order = -1;
        object->m_container = nullptr;
    }
}

void Container::ChangeOrder(Object* object, unsigned order)
{
    int newOrder = (order >= m_objects.size()) ? m_objects.size() - 1 : (int)order;
    if (object->m_order == newOrder) {
        return;
    }
    if (object->m_order < newOrder) {
        for (int i = object->m_order; i < newOrder; ++i) {
            m_objects[i] = m_objects[i + 1];
            m_objects[i]->m_order = i;
        }
    } else {
        for (int i = object->m_order; i > newOrder; --i) {
            m_objects[i] = m_objects[i - 1];
            m_objects[i]->m_order = i;
        }
    }
    m_objects[newOrder] = object;
    object->m_order = newOrder;
}
