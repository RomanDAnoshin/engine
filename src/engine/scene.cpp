#include "engine/scene.h"
using namespace engine;

Scene::Scene() :
    m_physics(nullptr)
{
    m_rootWidget.SetBackColor(Color(255, 255, 255, 0));
    m_rootWidget.SetAnchor(Anchor::All);
}

EntityContainer& Scene::GetRootEntity()
{
    return m_rootEntity;
}

WidgetContainer& Scene::GetRootWidget()
{
    return m_rootWidget;
}

Physics* Scene::GetPhysics() const
{
    return m_physics;
}

void Scene::SetPhysics(Physics* physics)
{
    m_physics = physics;
}

void Scene::HandleEvent(ALLEGRO_EVENT& event)
{
    m_rootWidget.HandleEvent(event);
}

void Scene::Update(const float dt)
{
    if (m_physics != nullptr) {
        m_physics->Update(dt);
    }
    m_rootEntity.Update(dt);
    m_rootWidget.Update(dt);
}

void Scene::Render(Renderer& renderer)
{
    renderer.ResetTransform();
    m_rootEntity.Render(renderer);

    renderer.ResetTransform();
    m_rootWidget.Render(renderer);
}
