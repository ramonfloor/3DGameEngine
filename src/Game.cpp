#include "Core/Application.hpp"

int main()
{
    rge::Application* app = rge::Application::Create("Game");
    app->Run();
    rge::Application::Destroy();
    return 0;
}