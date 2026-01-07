#include "Input.hpp"
#include "Application.hpp"
#include <GLFW/glfw3.h>

namespace rge
{
    bool Input::IsKeyPressed(KeyCode key)
    {
        GLFWwindow* window = Application::GetInstance()->GetWindow().GetWindow();
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::IsKeyRepeated(KeyCode key)
    {
        GLFWwindow* window = Application::GetInstance()->GetWindow().GetWindow();
        return glfwGetKey(window, key) == GLFW_REPEAT;
    }
    
    bool Input::IsKeyReleased(KeyCode key)
    {
        GLFWwindow* window = Application::GetInstance()->GetWindow().GetWindow();
        return glfwGetKey(window, key) == GLFW_RELEASE;
    }

    glm::vec2 Input::GetMousePosition()
    {
        GLFWwindow* window = Application::GetInstance()->GetWindow().GetWindow();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }
}