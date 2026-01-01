#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <print>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../glad/glad.h"

namespace rge {

    enum ShaderType {
        VERTEX = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };
    
    class Shader {
        public:
            Shader(std::string path, ShaderType type) {
                id = glCreateShader(type);
                std::string source = read_shader_file(path);
                const char* code = source.c_str();
                glShaderSource(id, 1, &code, NULL);
                compile();
            }
    
            GLuint getID() {
                return id;
            }
        
            void destroy() {
                glDeleteShader(id);
            }
    
        private:
            std::string read_shader_file(std::string& path) {
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
    
            void compile() {
                glCompileShader(id);
                int success;
                char infoLog[512];
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(id, 512, NULL, infoLog);
                    std::println("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog);
                }
            }
    
        private:
            ShaderType type;
            GLuint id;
    };
    
    class ShaderProgram {
        public:
            ShaderProgram() {
                id = glCreateProgram();
            }
    
            void attach(std::shared_ptr<Shader> shader) {
                shaders.push_back(shader);
                glAttachShader(id, shader->getID());
            }
    
            void link() {
                glLinkProgram(id);
                // check for linking errors
                int success;
                char infoLog[512];
                glGetProgramiv(id, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(id, 512, NULL, infoLog);
                    std::println("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}", infoLog);
                }
    
                for(auto s : shaders) {
                    s->destroy();
                }
    
                shaders.clear();
            }
    
            void use() {
                glUseProgram(id);
            }
    
            void set_uniform_mat4fv(std::string name, glm::mat4& matrix) {
                GLuint location = glGetUniformLocation(id, name.c_str());
                glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
            }
    
            void set_uniform4f(std::string name, float v0, float v1, float v2, float v3) {
                GLuint location = glGetUniformLocation(id, name.c_str());
                glUniform4f(location, v0, v1, v2, v3);
            }
    
            void set_uniform1f(std::string name, float v) {
                GLuint location = glGetUniformLocation(id, name.c_str());
                glUniform1f(location, v);
            }

            void set_uniform3f(std::string name, glm::vec3& value) {
                GLuint location = glGetUniformLocation(id, name.c_str());
                glUniform3f(location, value.x, value.y, value.z);
            }
    
            void destroy() {
                glDeleteProgram(id);
            }
    
        private:
            GLuint id;
            std::vector<std::shared_ptr<Shader>> shaders;
    };
}