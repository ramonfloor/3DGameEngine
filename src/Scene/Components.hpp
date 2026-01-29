#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/Mesh.hpp"

#include <memory>

struct TransformComponent
{
    glm::vec3 translation = glm::vec3(0.0f); // position x, y, z
    glm::vec3 rotation = glm::vec3(0.0f); // rotation in euler angles
    glm::vec3 scale = glm::vec3(1.0f); // scale factors x, y, z

    glm::mat4 GetTransform()
    {
        return glm::mat4(1.0f);
    }
};

struct IDComponent
{
    int id = 0;
};

struct CameraComponent
{
    Camera camera;
    bool primary = false;
};

struct MeshComponent
{
    std::shared_ptr<Mesh> mesh;
};

struct MaterialComponent
{
    std::shared_ptr<Shader> shader;
};

struct CubeColliderComponent
{
    float length;
};

struct SphereColliderComponent
{
    float radius;
};

struct CapsuleColliderComponent
{
    float length;
    float radius;
};

struct MeshColliderComponent
{
    
};