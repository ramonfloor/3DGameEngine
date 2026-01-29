#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <print>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"

class Shader 
{
    public:
        Shader(std::string vertex, std::string fragment) 
        {
            GLuint vertexID, fragmentID;
            vertexID = glCreateShader(GL_VERTEX_SHADER);
            fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertex_source = read_shader_file(vertex);
            std::string fragment_source = read_shader_file(fragment);
            const char* vertex_code = vertex_source.c_str();
            const char* fragment_code = fragment_source.c_str();
            glShaderSource(vertexID, 1, &vertex_code, NULL);
            glShaderSource(fragmentID, 1, &fragment_code, NULL);
            
            Compile(vertexID);
            Compile(fragmentID);
            
            m_id = glCreateProgram();
            glAttachShader(m_id, vertexID);
            glAttachShader(m_id, fragmentID);
            
            Link();

            glDeleteShader(vertexID);
            glDeleteShader(fragmentID);
        }

        ~Shader()
        {
            glDeleteProgram(m_id);
        }

        void Use()
        {
            glUseProgram(m_id);
        }

        void SetUniformMat4fv(std::string name, glm::mat4& matrix) {
            GLuint location = glGetUniformLocation(m_id, name.c_str());
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }

        void SetUniform4f(std::string name, float v0, float v1, float v2, float v3) {
            GLuint location = glGetUniformLocation(m_id, name.c_str());
            glUniform4f(location, v0, v1, v2, v3);
        }

        void SetUniform1f(std::string name, float v) {
            GLuint location = glGetUniformLocation(m_id, name.c_str());
            glUniform1f(location, v);
        }

        void SetUniform3f(std::string name, glm::vec3& value) {
            GLuint location = glGetUniformLocation(m_id, name.c_str());
            glUniform3f(location, value.x, value.y, value.z);
        }

    private:
        std::string read_shader_file(std::string& path) 
        {
            std::ifstream ShaderFile;
            std::string code;
            // ensure ifstream objects can throw exceptions:
            ShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try 
            {
                // open files
                ShaderFile.open(path);
                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << ShaderFile.rdbuf();
                ShaderFile.close();
                // convert stream into string
                code = vShaderStream.str();
            }
            catch(std::ifstream::failure e)
            {
                std::println("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
            }
            return code;
        }

        void Compile(GLuint shader_id) 
        {
            glCompileShader(shader_id);
            int success;
            char infoLog[512];
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
                std::println("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog);
            }
        }

        void Link() 
        {
            glLinkProgram(m_id);
            // check for linking errors
            int success;
            char infoLog[512];
            glGetProgramiv(m_id, GL_LINK_STATUS, &success);
            if (!success) 
            {
                glGetProgramInfoLog(m_id, 512, NULL, infoLog);
                std::println("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}", infoLog);
            }
        }


    private:
        GLuint m_id;
};
