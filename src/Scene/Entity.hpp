#pragma once

#include <cassert>
#include "entt/entt.hpp"

#include "Scene.hpp"

class Entity
{
    public:
        Entity(entt::entity handle, Scene* scene);

        template<typename ComponentType, typename... Args>
        void AddComponent(Args&&... args)
        {
            m_scene->m_registry.emplace<ComponentType>(m_handle, std::forward<Args>(args)...);
        }

        template<typename ComponentType>
        bool HasComponent()
        {
            return m_scene->m_registry.any_of<ComponentType>(m_handle);
        }

        template<typename ComponentType>
        ComponentType& GetComponent()
        {
            return m_scene->m_registry.get<ComponentType>(m_handle);
        }

        template<typename ComponentType>
        void RemoveComponent()
        {
            m_scene->m_registry.remove<ComponentType>(m_handle);
        }

    private:
        friend class Scene;
        entt::entity m_handle;
        Scene* m_scene;
};
