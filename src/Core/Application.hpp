#pragma once

#include "Window.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Scene/SceneLoader.hpp"
#include "../Scene/Scene.hpp"

#include <memory>
#include <print>
#include <string>

namespace rge {
    class Application {
        public:
            Application(std::string name) : m_window(name, 1000, 1000)
            {
                m_scene = SceneLoader::CreateBasicScene();
            }

            static Application* Create(std::string name)
            {
                if(!s_instance)
                {
                    s_instance = std::make_unique<Application>(name);
                }
                return s_instance.get();
            }

            void Run() 
            {
                while(!m_window.ShouldClose())
                {
                    float current_time = glfwGetTime();
                    float delta_time = current_time - m_last_frame_time;
                    m_last_frame_time = current_time;

                    m_scene->Update(delta_time);

                    bool p_down = Input::IsKeyPressed(KeyCode::KEY_P);
              
                    if(p_down && !m_pressed_last_frame)
                    {
                        std::println("Toggling polygon mode");
                        m_renderer.TogglePolygonMode();
                    }

                    m_pressed_last_frame = p_down;

                    m_renderer.Render(m_scene);

                    m_window.Update();
                }
            }

            static Application* GetInstance()
            {
                return s_instance.get();
            }

            Window& GetWindow()
            {
                return m_window;
            }

        private:
            Window m_window;
            std::shared_ptr<Scene> m_scene = nullptr;
            Renderer m_renderer;
            float m_last_frame_time = 0.0f;
            bool m_pressed_last_frame = false;

            // std::map<std::string, std::shared_ptr<Scene>> m_scenes; TODO: Scene management

        public:
            inline static std::unique_ptr<Application> s_instance = nullptr;
    };
}