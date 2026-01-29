#pragma once

#include "glad/glad.h"

#include <vector>
#include <print>
#include <memory>

class Scene;

class Renderer
{
    public:
        Renderer();

        ~Renderer();

        void Render(Scene* scene);
    
        void DrawMeshes(Scene* scene);
};