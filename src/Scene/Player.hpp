#pragma once

#include "Entity.hpp"
#include "../Core/Input.hpp"
#include "../Core/KeyCodes.hpp"
#include <print>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

namespace rge
{
    class Player : public Entity
    {
        public:
            Player() : Entity()
            {
                m_position = glm::vec3(0.0f, 0.5f, 0.0f);
                m_rotation = glm::vec3(0.0f, 1.0f, 0.0f);
            }

            void Update(float delta_time) override
            {
                Turn(delta_time);
                Move(delta_time);
            }

            float GetPitch()
            {
                return m_pitch;
            }

            float GetYaw()
            {
                return m_yaw;
            }

            float GetR()
            {
                return m_r;
            }

            float GetAlpha()
            {
                return m_alpha;
            }

        private:
            void Move(float delta_time)
            {
                float distance = delta_time * m_speed;

                if(Input::IsKeyPressed(KeyCode::KEY_W)) m_position += distance * m_front;
                if(Input::IsKeyPressed(KeyCode::KEY_S)) m_position -= distance * m_front;
                // if(Input::IsKeyPressed(KeyCode::KEY_A)) m_position.x -= distance;
                // if(Input::IsKeyPressed(KeyCode::KEY_D)) m_position.x += distance;
            }

            void Turn(float delta_time)
            {
                glm::vec2 mouse_pos = Input::GetMousePosition();
                static glm::vec2 last_mouse_pos = mouse_pos;

                float x_offset = mouse_pos.x - last_mouse_pos.x;
                float y_offset = last_mouse_pos.y - mouse_pos.y; // Reversed since y-coordinates go from bottom to top

                last_mouse_pos = mouse_pos;

                x_offset *= m_sensitivity * delta_time;
                y_offset *= m_sensitivity * delta_time;

                m_yaw -= x_offset;
                m_pitch += y_offset;

                // Constrain the pitch
                if(m_pitch > 89.0f) m_pitch = 89.0f;
                if(m_pitch < -89.0f) m_pitch = -89.0f;

                auto front = glm::vec3(sinf(m_yaw), 0.0f, cosf(m_yaw));
                m_front = glm::normalize(front);
            }

        private:
            float m_speed = 15.0f;

            float m_sensitivity = 2.0f;
            float m_pitch = 0.0f;
            float m_yaw = 0.0f;

            float m_r = 2.0f;
            float m_alpha = 30.0f;

            glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    };
}