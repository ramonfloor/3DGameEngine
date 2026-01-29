#pragma once

#include "entt/entt.hpp"

#include <unordered_map>

class Entity;

class Scene
{
    public:
        virtual void Update(float delta_time) {}

        Entity CreateEntity();

        void DestroyEntity(entt::entity entity);

        entt::registry& GetRegistry();

    protected:
        friend class Entity;

        entt::registry m_registry;
        std::unordered_map<int, entt::entity> m_entities;
};
