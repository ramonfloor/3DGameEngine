#pragma once

#include "Camera.hpp"
#include "Events/Event.hpp"

namespace rge
{
    class Player
    {
        public:
            void OnEvent(Event& e)
            {

            }

        private:
            glm::vec3 position;
            glm::vec3 direction;
            Camera camera;
    };
}
