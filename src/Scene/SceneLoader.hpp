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
                    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},  
                    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, //west face
                    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

                    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  
                    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, //east face
                    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

                    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},  
                    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, //north face
                    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
                    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},

                    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},  
                    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, //south face
                    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

                    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  
                    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, //top face
                    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
                    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

                    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  
                    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, //bottom face
                    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
                    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}
                };

                std::vector<unsigned int> indices = {
                    0, 1, 2, //west face
                    2, 3, 0,

                    4, 5, 6, //east face
                    6, 7, 4,

                    8, 9, 10, //north face
                    10, 11, 8,

                    12, 13, 14, //south face
                    14, 15, 12,

                    16, 17, 18, //top face
                    18, 19, 16,

                    20, 21, 22, //bottom face
                    22, 23, 20
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
                    {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
                    {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)}                   
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