#include "Application.hpp"

#include <filesystem>

std::unique_ptr<Application> Application::s_instance = nullptr;

Application::Application(std::string name) : m_window(name, 1000, 1000)
{
    std::filesystem::current_path(std::filesystem::path("/home/ramon/Programming/3DGameEngine/"));
    ShaderManager::LoadShader("src/Assets/Shaders/DefaultVertex.glsl", "src/Assets/Shaders/DefaultFragment.glsl", "DefaultShader");
    m_scene = SceneManager::CreateBasicScene();
}

Application* Application::Create(std::string name)
{
    if(!s_instance)
    {
        s_instance = std::make_unique<Application>(name);
    }
    return s_instance.get();
}

void Application::Run() 
{
    while(!m_window.ShouldClose())
    {
        float current_time = glfwGetTime();
        float delta_time = current_time - m_last_frame_time;
        m_last_frame_time = current_time;

        m_scene->Update(delta_time);

        m_renderer.Render(m_scene.get());

        m_window.Update();
    }
}

Application* Application::GetInstance()
{
    return s_instance.get();
}

Window& Application::GetWindow()
{
    return m_window;
}