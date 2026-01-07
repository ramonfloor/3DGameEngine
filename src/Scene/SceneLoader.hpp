#pragma once

#include "Scene.hpp"
#include <glm/glm.hpp>

#include <memory>

namespace rge
{
    class SceneLoader
    {
        public:
            static std::shared_ptr<Scene> CreateBasicScene()
            {
                std::shared_ptr<Scene> scene = std::make_shared<Scene>();

                std::shared_ptr<Mesh> terrain_mesh = CreateTerrain();
                std::shared_ptr<Entity> terrain = std::make_shared<Entity>();
                terrain->AddMesh(terrain_mesh);
                scene->AddEntity(terrain);

                return scene;
            }

            static std::shared_ptr<Mesh> CreateTerrain()
            {
                int widthX = 500;
                int widthZ = 500;
                float scale = 1.0f;

                std::vector<Vertex> vertices;
                std::vector<unsigned int> indices;

                for(int z = 0; z <= widthZ; z++)
                {
                    for(int x = 0; x <= widthX; x++)
                    {
                        float y = 0.0f;
                        vertices.push_back({glm::vec3(x * scale, y, z * scale), glm::vec3(0.8f, 0.8f, 0.8f), CalculateNormal(x, z)});
                    }
                }

                for (int z = 0; z < widthZ; z++)
                {
                    for (int x = 0; x < widthX; x++)
                    {
                        int i0 = x + (widthX + 1) * z;           // current
                        int i1 = (x + 1) + (widthX + 1) * z;     // right
                        int i2 = x + (widthX + 1) * (z + 1);     // down
                        int i3 = (x + 1) + (widthX + 1) * (z + 1); // right-down

                        // triangle 1
                        indices.push_back(i0);
                        indices.push_back(i2);
                        indices.push_back(i1);

                        // triangle 2
                        indices.push_back(i1);
                        indices.push_back(i2);
                        indices.push_back(i3);
                    }
                }

                std::shared_ptr<Shader> terrain_vertex = std::make_shared<Shader>("/home/ramon/Programming/3DGameEngine/src/Shaders/PlaneVertex.glsl", VERTEX);
                std::shared_ptr<Shader> terrain_fragment = std::make_shared<Shader>("/home/ramon/Programming/3DGameEngine/src/Shaders/PlaneFragment.glsl", FRAGMENT);
                std::shared_ptr<ShaderProgram> terrain_program = std::make_shared<ShaderProgram>();
                terrain_program->attach(terrain_vertex);
                terrain_program->attach(terrain_fragment);
                terrain_program->link();
                std::shared_ptr<Mesh> terrain_mesh = std::make_shared<Mesh>(vertices, indices, terrain_program);

                return terrain_mesh;
            }

            static float Height(int x, int z)
            {
                return 5 * sin(x * 0.1f) * cos(z * 0.1f);
            }

            static glm::vec3 CalculateNormal(int x, int z)
            {
                // float hl = Height(x - 1, z);
                // float hr = Height(x + 1, z);
                // float hd = Height(x, z - 1);
                // float hu = Height(x, z + 1);

                // glm::vec3 normal = glm::vec3(
                //     hl - hr,
                //     2.0f,
                //     hd - hu
                // );

                // return glm::normalize(normal);

                return glm::vec3(0.0f, 1.0f, 0.0f);
            }
    };
}