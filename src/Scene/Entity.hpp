#pragma once

#include <vector>
#include <memory>

#include "../Renderer/Mesh.hpp"
#include "../Camera.hpp"

namespace rge
{
    class Entity
    {
        public:
            Entity()
            {

            }

            virtual void Update(float delta_time)
            { 
                // do some calculations (position, etc.)
            }

            std::shared_ptr<Mesh> GetMesh()
            {
                return m_mesh;
            }

            glm::vec3& GetPosition()
            {
                return m_position;
            }

            glm::vec3& GetRotation()
            {
                return m_rotation;
            }

            float GetScale()
            {
                return m_scale;
            }

            float GetAngle()
            {
                return m_angle;
            }

            Camera& GetCamera()
            {
                return m_camera;
            }

            void AddMesh(std::shared_ptr<Mesh> mesh)
            {
                m_mesh = mesh;
            }

        protected:
            glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 m_rotation = glm::vec3(1.0f);
            float m_scale = 1.0f;
            float m_angle = 0.0f;
            std::shared_ptr<Mesh> m_mesh = nullptr;
            Camera m_camera;
    };
}