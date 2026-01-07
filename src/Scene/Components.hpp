#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "Camera.hpp"
#include "../Renderer/Mesh.hpp"

namespace rge
{
    struct TransformComponent
    {
        glm::vec3 translation;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 GetTransform()
        {
            return glm::mat4(1.0f);
        }
    };

    struct CameraComponent
    {
        Camera camera;
        bool primary;
    };

    struct MeshComponent
    {
        std::shared_ptr<Mesh> mesh;
    };
}