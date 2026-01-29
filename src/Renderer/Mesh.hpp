#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <vector>
#include <string>
#include <memory>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
};

class Mesh
{
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
        {
            p_vertices = vertices;
            p_indices = indices;
            SetupMesh();
        }

        ~Mesh()
        {
            glDeleteBuffers(1, &m_vbo);
            glDeleteBuffers(1, &m_ebo);
            glDeleteVertexArrays(1, &m_vao);
        }

        const GLuint GetVAO()
        {
            return m_vao;
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

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
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
};