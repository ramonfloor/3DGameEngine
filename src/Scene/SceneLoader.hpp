#pragma once

#include "Scene.hpp"
#include <glm/glm.hpp>

#include "Player.hpp"
#include "Plane.cpp"

#include <memory>

namespace rge
{
    class SceneLoader
    {
        public:
            static std::shared_ptr<Scene> CreateBasicScene()
            {
                std::shared_ptr<Scene> scene = std::make_shared<Scene>();

                std::vector<Vertex> vertices = {
                    // West face (x = -0.5, normal = (-1, 0, 0))
                    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

                    // East face (x = 0.5, normal = (1, 0, 0))
                    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
                    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
                    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

                    // North face (z = -0.5, normal = (0, 0, -1))
                    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},

                    // South face (z = 0.5, normal = (0, 0, 1))
                    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
                    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
                    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

                    // Top face (y = 0.5, normal = (0, 1, 0))
                    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
                    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
                    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

                    // Bottom face (y = -0.5, normal = (0, -1, 0))
                    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
                    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
                    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
                    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}
                };

                std::vector<unsigned int> indices = {
                    0, 1, 2, //west face
                    2, 3, 0,

                    4, 5, 6, //east face
                    6, 7, 4,

                    10, 9, 8, //north face (flipped)
                    8, 11, 10,

                    14, 13, 12, //south face (flipped)
                    12, 15, 14,

                    18, 17, 16, //top face (flipped)
                    16, 19, 18,

                    22, 21, 20, //bottom face (flipped)
                    20, 23, 22
                };

                std::shared_ptr<Shader> player_vertex = std::make_shared<Shader>("/home/ramon/Programming/GameEngine/src/Shaders/PlayerVertex.glsl", VERTEX);
                std::shared_ptr<Shader> player_fragment = std::make_shared<Shader>("/home/ramon/Programming/GameEngine/src/Shaders/PlayerFragment.glsl", FRAGMENT);
                std::shared_ptr<ShaderProgram> player_program = std::make_shared<ShaderProgram>();
                player_program->attach(player_vertex);
                player_program->attach(player_fragment);
                player_program->link();
                std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices, player_program);
                std::shared_ptr<Player> object = std::make_shared<Player>();
                object->AddMesh(mesh);
                scene->AddEntity(object);
                scene->SetPlayerEntity(object);

                std::vector<Vertex> plane = {
                    {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f)}                   
                };

                std::vector<unsigned int> plane_indices = {
                    0, 1, 3,
                    3, 2, 0
                };

                std::shared_ptr<Shader> plane_vertex = std::make_shared<Shader>("/home/ramon/Programming/GameEngine/src/Shaders/PlaneVertex.glsl", VERTEX);
                std::shared_ptr<Shader> plane_fragment = std::make_shared<Shader>("/home/ramon/Programming/GameEngine/src/Shaders/PlaneFragment.glsl", FRAGMENT);
                std::shared_ptr<ShaderProgram> plane_program = std::make_shared<ShaderProgram>();
                plane_program->attach(plane_vertex);
                plane_program->attach(plane_fragment);
                plane_program->link();
                std::shared_ptr<Mesh> plane_mesh = std::make_shared<Mesh>(plane, plane_indices, plane_program);
                std::shared_ptr<Plane> plane_object = std::make_shared<Plane>();
                plane_object->AddMesh(plane_mesh);
                scene->AddEntity(plane_object);

                return scene;
            }
    };
}