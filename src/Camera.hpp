#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

        private:
            void CalculateProjection()
            {
                m_projection_matrix = glm::perspective(m_fov, m_aspect, m_near, m_far);
            }
    
        private:
            float m_fov = glm::radians(45.0f);
            float m_near = 0.1f;
            float m_far = 1000.0f;
            float m_aspect = 1.0f;

            glm::mat4 m_projection_matrix = glm::mat4(1.0f);
    };
}