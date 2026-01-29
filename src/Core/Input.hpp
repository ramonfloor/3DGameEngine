#pragma once

#include <glm/glm.hpp>
#include "KeyCodes.hpp"

class Input
{
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsKeyRepeated(KeyCode key);
        static bool IsKeyReleased(KeyCode key);
        static glm::vec2 GetMousePosition();
};