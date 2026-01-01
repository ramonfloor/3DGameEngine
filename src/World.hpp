#pragma once

#include "Scene/SceneLoader.hpp"

#include <print>
#include <memory>

namespace rge
{   
    class World
    {
        public:
            World()
            {
                m_active_scene = SceneLoader::CreateBasicScene();
            }

            ~World()
            {

            }

            void Update(float delta_time)
            {
                m_active_scene->Update(delta_time);
            }

            std::shared_ptr<Scene> GetActiveScene()
            {
                return m_active_scene;
            }

        private:
            std::shared_ptr<Scene> m_active_scene;
    };
}
