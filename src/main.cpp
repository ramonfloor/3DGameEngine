#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <array>
#include <print>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"


using namespace rge;

void framebuffer_size_callback(int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput();

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

float yaw = -90.0f;
float pitch = 0.0f;
glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 front;
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

float delta_time = 0.0f;
float last_frame = 0.0f;
float current_frame = 0.0f;

float last_x = 500.0f;
float last_y = 500.0f;
bool first_mouse = true;

Camera cam(45.0f, -90.0f, 0.0f);
Window window("Game", SCR_WIDTH, SCR_HEIGHT);

int main()
{
    glfwSetCursorPosCallback(window.GetWindow(), mouse_callback);

    Shader vertex_shader("/home/ramon/Programming/OpenGL/src/Shaders/vertex.glsl", VERTEX);
    Shader fragment_shader("/home/ramon/Programming/OpenGL/src/Shaders/fragment.glsl", FRAGMENT);

    ShaderProgram program;
    program.attach(vertex_shader);
    program.attach(fragment_shader);
    program.link();

    struct Vertex {
        glm::vec3 position;
    };

    std::vector<Vertex> vertices = {
                    {glm::vec3(-0.5f, -0.5f, 0.5f)},  
                    {glm::vec3(-0.5f, -0.5f, -0.5f)}, //west face
                    {glm::vec3(-0.5f, 0.5f, -0.5f)},
                    {glm::vec3(-0.5f, 0.5f, 0.5f)},

                    {glm::vec3(0.5f, -0.5f, 0.5f)},  
                    {glm::vec3(0.5f, -0.5f, -0.5f)}, //east face
                    {glm::vec3(0.5f, 0.5f, -0.5f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f)},

                    {glm::vec3(0.5f, -0.5f, -0.5f)},  
                    {glm::vec3(-0.5f, -0.5f, -0.5f)}, //north face
                    {glm::vec3(-0.5f, 0.5f, -0.5f)},
                    {glm::vec3(0.5f, 0.5f, -0.5f)},

                    {glm::vec3(0.5f, -0.5f, 0.5f)},  
                    {glm::vec3(-0.5f, -0.5f, 0.5f)}, //south face
                    {glm::vec3(-0.5f, 0.5f, 0.5f)},
                    {glm::vec3(0.5f, 0.5f, 0.5f)},

                    {glm::vec3(-0.5f, 0.5f, 0.5f)},  
                    {glm::vec3(0.5f, 0.5f, 0.5f)}, //top face
                    {glm::vec3(0.5f, 0.5f, -0.5f)},
                    {glm::vec3(-0.5f, 0.5f, -0.5f)},

                    {glm::vec3(-0.5f, -0.5f, 0.5f)},  
                    {glm::vec3(0.5f, -0.5f, 0.5f)}, //bottom face
                    {glm::vec3(0.5f, -0.5f, -0.5f)},
                    {glm::vec3(-0.5f, -0.5f, -0.5f)}
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

    glEnable(GL_DEPTH_TEST);

    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // position
    
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); 
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        processInput();

        program.use();
        // program.set_uniform4f("color", 1.0f, 0.0f, 0.0f, 1.0f);

        view = cam.GetView();
        projection = glm::perspective(cam.m_fov, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        model = glm::mat4(1.0f);

        program.set_uniform_mat4fv("view", view);
        program.set_uniform_mat4fv("projection", projection);
        
        program.set_uniform_mat4fv("model", model);
        
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0); 

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    program.destroy();

    return 0;
}

void processInput()
{
    float speed = 5.0f * delta_time;

    if(glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window.GetWindow(), true);
    }
    if(glfwGetKey(window.GetWindow(), GLFW_KEY_W))
    {
        cam.position += speed * cam.front;
    }
    if(glfwGetKey(window.GetWindow(), GLFW_KEY_S))
    {
        cam.position -= speed * cam.front;
    }
    if(glfwGetKey(window.GetWindow(), GLFW_KEY_A))
    {
        cam.position -= speed * glm::normalize(glm::cross(cam.front, cam.up));
    }
    if(glfwGetKey(window.GetWindow(), GLFW_KEY_D))
    {
        cam.position += speed * glm::normalize(glm::cross(cam.front, cam.up));
    }
}

void framebuffer_size_callback(int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double x, double y)
{
    if (first_mouse)
    {
        last_x = x;
        last_y = y;
        first_mouse = false;
    }

    float offset_x = x - last_x;
    float offset_y = last_y - y;
    last_x = x;
    last_y = y;

    const float x_sensitvity = 0.4f;
    const float y_sensitvity = 0.1f;
    offset_x *= x_sensitvity;
    offset_y += y_sensitvity;

    cam.m_yaw += offset_x;
    cam.m_pitch += offset_y;

    if(cam.m_pitch > 89.0f) {
        cam.m_pitch = 89.0f;
    }
    if(cam.m_pitch < -89.0f) {
        cam.m_pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(cam.m_yaw)) * cos(glm::radians(cam.m_pitch));
    direction.y = sin(glm::radians(cam.m_pitch));
    direction.z = sin(glm::radians(cam.m_yaw)) * cos(glm::radians(cam.m_pitch));
    cam.front = glm::normalize(direction);
}
