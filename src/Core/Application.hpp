#pragma once

#include "Window.hpp"
#include "../Renderer/Renderer.hpp"
#include "../World.hpp"

#include <memory>
#include <print>
#include <string>

namespace rge {
    class Application {
        private:
            Application(std::string name) : m_window(name, 1000, 1000)
            {
                
            }

        public:
            static Application* Create(std::string name)
            {
                if(!s_instance)
                {
                    s_instance = new Application(name);
                }
                return s_instance;
            }

            static void Destroy()
            {
                delete s_instance;
                s_instance = nullptr;
            }

            void Run() 
            {
                while(!m_window.ShouldClose())
                {
                    float current_time = glfwGetTime();
                    float delta_time = current_time - m_last_frame_time;
                    m_last_frame_time = current_time;

                    // std::println("FPS: {}", 1.0f / delta_time);

                    m_world.Update(delta_time);

                    m_renderer.Render(m_world.GetActiveScene());

                    m_window.Update();
                }
            }

            static Application& GetInstance()
            {
                return *s_instance;
            }

            Window& GetWindow()
            {
                return m_window;
            }

        private:
            Window m_window;
            World m_world;
            Renderer m_renderer;
            float m_last_frame_time = 0.0f;

        public:
            static Application* s_instance;
    };
}