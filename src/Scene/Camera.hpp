#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Entity.hpp"

namespace rge {
    class Camera
    {
        public:
            Camera()
            {
                CalculateProjection();
            }

            const glm::mat4& GetProjection()
            {
                return m_projection_matrix;
            }

            void Update(float delta_time)
            {
                Turn(delta_time);
                Move(delta_time);
            }

            glm::vec3& GetPosition()
            {
                return m_position;
            }

            glm::vec3& GetFront()
            {
                return m_front;
            }

        private:
            void CalculateProjection()
            {
                m_projection_matrix = glm::perspective(m_fov, m_aspect, m_near, m_far);
            }

            void Move(float delta_time)
            {
                float distance = delta_time * m_speed;

                glm::vec3 front_xz = glm::vec3(m_front.x, 0.0f, m_front.z);
                front_xz = glm::normalize(front_xz);

                glm::vec3 side = glm::cross(front_xz, glm::vec3(0.0f, 1.0f, 0.0f));
                side.y = 0.0f;
                side = glm::normalize(side);

                if(Input::IsKeyPressed(KeyCode::KEY_W)) m_position += distance * front_xz;
                if(Input::IsKeyPressed(KeyCode::KEY_S)) m_position -= distance * front_xz;
                if(Input::IsKeyPressed(KeyCode::KEY_SPACE)) m_position.y += distance;
                if(Input::IsKeyPressed(KeyCode::KEY_LEFT_SHIFT)) m_position.y -= distance;
                if(Input::IsKeyPressed(KeyCode::KEY_A)) m_position -= distance * side;
                if(Input::IsKeyPressed(KeyCode::KEY_D)) m_position += distance * side;
            }

            void Turn(float delta_time)
            {
                glm::vec2 mouse_pos = Input::GetMousePosition();
                static glm::vec2 last_mouse_pos = mouse_pos;

                float x_offset = mouse_pos.x - last_mouse_pos.x;
                float y_offset = last_mouse_pos.y - mouse_pos.y;

                last_mouse_pos = mouse_pos;

                x_offset *= m_sensitivity * delta_time;
                y_offset *= m_sensitivity * delta_time;

                m_yaw -= x_offset;
                m_pitch += y_offset;

                if(m_pitch > 89.0f) m_pitch = 89.0f;
                if(m_pitch < -89.0f) m_pitch = -89.0f;

                auto front = glm::vec3(sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch)), sinf(glm::radians(m_pitch)), cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch)));
                m_front = glm::normalize(front);
            }
    
        private:
            float m_fov = glm::radians(45.0f);
            float m_near = 0.1f;
            float m_far = 1000.0f;
            float m_aspect = 1.0f;

            glm::mat4 m_projection_matrix = glm::mat4(1.0f);

            glm::vec3 m_position = glm::vec3(0.0f, 10.0f, 0.0f);
            glm::vec3 m_front = glm::vec3(0.0f, 0.0f, 1.0f);
            glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
            float m_speed = 100.0f;
            float m_sensitivity = 20.0f;
            float m_yaw = 0.0f;
            float m_pitch = 0.0f;
    };
}