#pragma once

#include "glad/glad.h"

#include <vector>
#include <print>
#include <memory>

#include "../Scene/Scene.hpp"
#include "../Scene/Camera.hpp"
#include "Shader.hpp"

namespace rge 
{
    class Renderer
    {
        public:
            Renderer()
            {
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);
            }

            ~Renderer()
            {

            }

            void Render(std::shared_ptr<Scene> scene)
            {
                glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                Camera& camera = scene->GetCamera();
                auto cam_pos = camera.GetPosition();
                auto cam_front = camera.GetFront();
                auto view = glm::lookAt(cam_pos, cam_pos + cam_front, glm::vec3(0.0f, 1.0f, 0.0f));
                auto projection = camera.GetProjection();

                for(auto e : scene->GetEntities())
                {
                    Draw(e, scene->GetLightPosition(), view, projection, cam_pos);
                }
            }

            void TogglePolygonMode()
            {
                if(m_polygon_mode)
                {
                    m_polygon_mode = false;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                else
                {
                    m_polygon_mode = true;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
        
            private:
                bool m_polygon_mode = false;
    };
}