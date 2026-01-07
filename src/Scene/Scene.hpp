#pragma once

#include "Entity.hpp"
#include "Camera.hpp"

#include <print>

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
                UpdateLight(delta_time);
                m_camera.Update(delta_time);
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

            Camera& GetCamera()
            {
                return m_camera;
            }

        private:
            void UpdateLight(float delta_time)
            {
                float z = sinf(m_time);
                float y = cosf(m_time);

                float radius = 500.0f;

                m_light_position.y = radius * y;
                m_light_position.z = radius * z + 250.0f;
            }

        private:
            std::vector<std::shared_ptr<Entity>> m_entities;
            glm::vec3 m_light_position = glm::vec3(250.0f, 0.0f, 250.0f);
            float m_time = 0.0f;
            Camera m_camera;
    };
}