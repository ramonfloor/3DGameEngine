#pragma once

#include "Input.hpp"
#include "KeyCodes.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <memory>
#include <print>

namespace rge 
{
    class Window 
    {
        public:
            Window(std::string name, int width, int height) : m_name(name), m_width(width), m_height(height)
            {
                InitWindow();
    
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::println("Failed to initialize GLAD");
                }
            } 
            
            ~Window() 
            {
                glfwTerminate();
            }
    
            int GetHeight() 
            {
                return m_height;
            }
    
            int GetWidth()
            {
                return m_width;
            }
    
            GLFWwindow* GetWindow()
            {
                return m_window;
            }
    
            bool ShouldClose()
            {
                return glfwWindowShouldClose(m_window);
            }

            void Update()
            {
                if(Input::IsKeyPressed(KeyCode::KEY_ESCAPE))
                {
                    glfwSetWindowShouldClose(m_window, true);
                }
                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }
        
        private:
            void InitWindow()
            {
                int init = glfwInit();
                
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
                glfwWindowHint(GLFW_SAMPLES, 32);
                glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
                
                m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
                if (m_window == NULL)
                {
                    std::println("Failed to create GLFW window");
                    glfwTerminate();
                    return;
                }
                glfwMakeContextCurrent(m_window);
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSwapInterval(0);
            }
    
        private:
            std::string m_name;
            int m_width;
            int m_height;
            GLFWwindow* m_window;
    };
}