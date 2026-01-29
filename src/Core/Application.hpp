#pragma once

#include "Window.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/ShaderManager.hpp"
#include "../Scene/SceneManager.hpp"
#include "../Scene/Scene.hpp"

#include <memory>
#include <print>
#include <string>

class Application {
    public:
        Application(std::string name);

        static Application* Create(std::string name);

        void Run();

        static Application* GetInstance();

        Window& GetWindow();

    private:
        Window m_window;
        Renderer m_renderer;
        std::shared_ptr<Scene> m_scene = nullptr;
        float m_last_frame_time = 0.0f;

    public:
        static std::unique_ptr<Application> s_instance;
};