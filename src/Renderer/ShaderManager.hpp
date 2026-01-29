#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "Shader.hpp"


class ShaderManager
{
    public:
        static void LoadShader(std::string vertex_path, std::string fragment_path, std::string name)
        {
            m_shaders.emplace(name, std::make_shared<Shader>(vertex_path, fragment_path));
        }

        static std::shared_ptr<Shader> GetShader(std::string name)
        {
            return m_shaders[name];
        }

    private:
        inline static std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders{};
};