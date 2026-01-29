#include "Core/Application.hpp"

#include <thread>
#include <chrono>

int main()
{
    Application* app = Application::Create("Game");
    app->Run();
    return 0;
}