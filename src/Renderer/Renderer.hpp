#pragma once

#include "glad/glad.h"

#include <vector>
#include <print>
#include <memory>

#include "../Scene/Scene.hpp"
#include "../Camera.hpp"
#include "Shader.hpp"

namespace rge 
{
    class Renderer
    {
        public:
            Renderer()
            {
                glEnable(GL_DEPTH_TEST);
            }

            ~Renderer()
            {

            }

            void Render(std::shared_ptr<Scene> scene)
            {
                glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                std::shared_ptr<Player> entity = scene->GetPlayerEntity();
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                glm::vec3 eye = entity->GetPosition() + glm::vec3(sinf(entity->GetYaw()) * entity->GetR() * tan(entity->GetAlpha()), 4.0f, cosf(entity->GetYaw()) * entity->GetR() * tan(entity->GetAlpha()));
                glm::vec3 view_direction = glm::vec3(sinf(entity->GetYaw()) * entity->GetR() * tan(entity->GetAlpha()), 4.0f, cosf(entity->GetYaw()) * entity->GetR() * tan(entity->GetAlpha())) - entity->GetPosition();
                auto view = glm::lookAt(eye, entity->GetPosition(), up);
                glm::mat4 projection = entity->GetCamera().GetProjection();

                for(auto e : scene->GetEntities())
                {
                    Draw(e, scene->GetLightPosition(), view, projection, eye);
                }
            }
        
        private:
            void Draw(std::shared_ptr<Entity> entity, glm::vec3 light_position, glm::mat4& view, glm::mat4& projection, glm::vec3 view_position)
            {
                auto mesh = entity->GetMesh();
                auto shader_program = mesh->GetShaderProgram();
                
                shader_program->use();

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, entity->GetPosition());
                model = glm::rotate(model, glm::radians(entity->GetAngle()), entity->GetRotation());
                model = glm::scale(model, glm::vec3(entity->GetScale()));

                glm::mat4 normal_matrix = glm::transpose(glm::inverse(model));

                shader_program->set_uniform_mat4fv("view", view);
                shader_program->set_uniform_mat4fv("projection", projection);
                shader_program->set_uniform_mat4fv("model", model);
                shader_program->set_uniform_mat4fv("normal_matrix", normal_matrix);
                shader_program->set_uniform3f("LightPos", light_position);
                shader_program->set_uniform3f("ViewPos", view_position);

                glBindVertexArray(mesh->GetVAO());

                glDrawElements(GL_TRIANGLES, mesh->p_indices.size(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
    };
}