#include "Entity.hpp"
#include "../Core/Input.hpp"
#include "../Core/KeyCodes.hpp"

namespace rge
{
    class Plane : public Entity
    {
        public:
            Plane()
            {
                m_position = glm::vec3(0.0f, 0.0f, 0.0f);
                m_rotation = glm::vec3(1.0f, 0.0f, 0.0f);
                m_angle = 90.0f;
                m_scale = 50.0f;
            }

            void Update(float delta_time) override
            {
                
            }
    };
}