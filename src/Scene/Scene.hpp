#pragma once

#include "Entity.hpp"
#include "Player.hpp"

#include <memory>

namespace rge
{
    class Scene
    {
        public:
            Scene()
            {

            }

            void Update(const float delta_time)
            {
                m_time += delta_time;
                // UpdateLight(delta_time);
                for(auto& o : m_entities)
                {
                    o->Update(delta_time);
                }
            }

            std::vector<std::shared_ptr<Entity>>& GetEntities()
            {
                return m_entities;
            }

            glm::vec3& GetLightPosition()
            {
                return m_light_position;
            }

            void AddEntity(const std::shared_ptr<Entity> o)
            {
                m_entities.push_back(o);
            }

            void SetPlayerEntity(const std::shared_ptr<Player> o)
            {
                m_player_entity = o;
            }

            std::shared_ptr<Player> GetPlayerEntity()
            {
                return m_player_entity;
            }

        private:
            void UpdateLight(float delta_time)
            {
                float z = sinf(m_time);
                float y = cosf(m_time);

                float radius = 10.0f;

                m_light_position.x = (-1.0f) * radius * z;
                m_light_position.y = radius * y;
                m_light_position.z = radius * z;
            }

        private:
            std::vector<std::shared_ptr<Entity>> m_entities;
            glm::vec3 m_light_position = glm::vec3(5.0f, 10.0f, 5.0f);
            float m_time = 0.0f;
            std::shared_ptr<Player> m_player_entity = nullptr;
    };
}