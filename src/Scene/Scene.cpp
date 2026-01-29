#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"

Entity Scene::CreateEntity()
{
    entt::entity handle = m_registry.create();
    int id = 0;

    Entity entity(handle, this);
    entity.AddComponent<TransformComponent>();
    entity.AddComponent<IDComponent>(id);

    m_entities[id] = handle;
    return entity;
}

void Scene::DestroyEntity(entt::entity entity)
{
    int id = m_registry.get<IDComponent>(entity).id;
    m_entities.erase(id);
    m_registry.destroy(entity);
}

entt::registry& Scene::GetRegistry()
{
    return m_registry;
}