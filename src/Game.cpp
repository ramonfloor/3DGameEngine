#include "Core/Application.hpp"

int main()
{
    rge::Application* app = rge::Application::Create("Game");
    app->Run();
    return 0;
}