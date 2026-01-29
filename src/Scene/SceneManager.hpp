#pragma once

#include "Scene.hpp"
#include "../Renderer/Mesh.hpp"
#include <glm/glm.hpp>
#include "Components.hpp"
#include "../Renderer/ShaderManager.hpp"
#include "Entity.hpp"

#include <memory>
#include <vector>

class GameScene : public Scene
{
    void Update(float delta_time) override {
        CameraMovementSystem(delta_time);
    }

    void CameraMovementSystem(float delta_time)
    {
        float speed = 5.0f * delta_time;
        auto view = m_registry.view<CameraComponent>();
        for(auto e : view)
        {
            Entity entity(e, this);
            auto cam = entity.GetComponent<CameraComponent>();
            if(cam.primary)
            {
                auto& transform = entity.GetComponent<TransformComponent>();
                if(Input::IsKeyPressed(KeyCode::KEY_W))
                {
                    transform.translation.z -= speed;
                }
                if(Input::IsKeyPressed(KeyCode::KEY_S))
                {
                    transform.translation.z += speed;
                }
                if(Input::IsKeyPressed(KeyCode::KEY_A))
                {
                    transform.translation.x -= speed;
                }
                if(Input::IsKeyPressed(KeyCode::KEY_D))
                {
                    transform.translation.x += speed;
                }
                if(Input::IsKeyPressed(KeyCode::KEY_SPACE))
                {
                    transform.translation.y += speed;
                }
                if(Input::IsKeyPressed(KeyCode::KEY_LEFT_SHIFT))
                {
                    transform.translation.y -= speed;
                }
            }
        }
    }
};

class SceneManager
{
    public:
        static std::shared_ptr<Scene> CreateBasicScene()
        {
            std::shared_ptr scene = std::make_shared<GameScene>();
            auto cube = scene->CreateEntity();
            auto cam = scene->CreateEntity();
            cam.AddComponent<CameraComponent>(Camera(), true);
            
            auto c = GenerateCube();
            cube.AddComponent<MeshComponent>(c);
            std::shared_ptr<Shader> shader = ShaderManager::GetShader("DefaultShader");
            cube.AddComponent<MaterialComponent>(shader);

            return scene;
        }

        static std::shared_ptr<Mesh> GenerateCube()
        {
            std::vector<unsigned int> indices = {
                //Top
                0, 1, 2,
                2, 3, 1,

                //Bottom
                4, 5, 6,
                6, 7, 5,

                //Front
                8, 9, 10,
                10, 11, 9,

                //Back
                12, 13, 14,
                14, 15, 13,

                //Left
                16, 17, 18,
                18, 19, 17,

                //Right
                20, 21, 22, 
                22, 23, 21
            };


            std::vector<Vertex> vertices = {
                //Top
                {{-1.0, 1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 1.0f, 0.0f}},
                {{1.0f, 1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 1.0f, 0.0f}},
                {{-1.0f, 1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 1.0f, 0.0f}},
                {{1.0f, 1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 1.0f, 0.0f}},

                //Bottom
                {{-1.0f, -1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f}},
                {{1.0f, -1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f}},
                {{-1.0f, -1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f}},
                {{1.0f, -1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f}},

                //Front
                {{-1.0f,  1.0f, 1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, 1.0f}},
                {{1.0f,  1.0f, 1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, 1.0f}},
                {{-1.0f, -1.0f, 1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, 1.0f}},
                {{1.0f, -1.0f, 1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, 1.0f}},

                //Back
                {{-1.0f, 1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, -1.0f}},
                {{1.0f, 1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, -1.0f}},
                {{-1.0f, -1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, -1.0f}},
                {{1.0f, -1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {0.0f, 0.0f, -1.0f}},

                //Left
                {{-1.0f,  1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {-1.0f, 0.0f, 0.0f}},
                {{-1.0f,  1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {-1.0f, 0.0f, 0.0f}},
                {{-1.0f, -1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {-1.0f, 0.0f, 0.0f}},
                {{-1.0f, -1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {-1.0f, 0.0f, 0.0f}},

                //Right
                {{1.0f,  1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {1.0f, 0.0f, 0.0f}},
                {{1.0f,  1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {1.0f, 0.0f, 0.0f}},
                {{1.0f, -1.0f,  1.0f}, {0.7f, 0.7f, 0.7f}, {1.0f, 0.0f, 0.0f}},
                {{1.0f, -1.0f, -1.0f}, {0.7f, 0.7f, 0.7f}, {1.0f, 0.0f, 0.0f}}
            };

            std::shared_ptr mesh = std::make_shared<Mesh>(vertices, indices);

            return mesh;
        }
};