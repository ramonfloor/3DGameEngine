#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

        void SetDimensions(const float width, const float height)
        {
            m_width = width;
            m_height = height;
        }

    private:
        void CalculateProjection()
        {
            float aspect = m_width / m_height;
            m_projection_matrix = glm::perspective(m_fov, aspect, m_near, m_far);
        }

    private:
        float m_fov = glm::radians(45.0f);
        float m_near = 0.1f;
        float m_far = 1000.0f;
        float m_width = 800.0f;
        float m_height = 800.0f;

        glm::mat4 m_projection_matrix = glm::mat4(1.0f);
};