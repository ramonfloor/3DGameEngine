#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.hpp"

#include <vector>
#include <string>

namespace rge
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal;
    };

    class Mesh
    {
        public:
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<ShaderProgram> program)
            {
                p_vertices = vertices;
                p_indices = indices;
                m_shader_program = program;
                SetupMesh();
            }

            ~Mesh()
            {
                glDeleteVertexArrays(1, &m_vao);
                glDeleteBuffers(1, &m_vbo);
                glDeleteBuffers(1, &m_ebo);
            }

            const GLuint GetVAO()
            {
                return m_vao;
            }

            std::shared_ptr<ShaderProgram> GetShaderProgram()
            {
                return m_shader_program;
            }

        public:
            std::vector<Vertex> p_vertices;
            std::vector<unsigned int> p_indices;

        private:
            void SetupMesh()
            {
                glGenVertexArrays(1, &m_vao);
                glGenBuffers(1, &m_vbo);
                glGenBuffers(1, &m_ebo);

                glBindVertexArray(m_vao);

                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferData(GL_ARRAY_BUFFER, p_vertices.size() * sizeof(Vertex), p_vertices.data(), GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indices.size() * sizeof(unsigned int), p_indices.data(), GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);

                glBindVertexArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }

        private:
            GLuint m_vao;
            GLuint m_vbo;
            GLuint m_ebo;

            std::shared_ptr<ShaderProgram> m_shader_program;
    };
}