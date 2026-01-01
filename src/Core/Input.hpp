#pragma once

#include "KeyCodes.hpp"
#include <glm/glm.hpp>

namespace rge
{
    class Input
    {
        public:
            static bool IsKeyPressed(KeyCode key);
            static bool IsKeyRepeated(KeyCode key);
            static bool IsKeyReleased(KeyCode key);
            static glm::vec2 GetMousePosition();
    };
}