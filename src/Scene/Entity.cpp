#include "Entity.hpp"
#include "Scene.hpp"

Entity::Entity(entt::entity handle, Scene* scene) : m_handle(handle), m_scene(scene) {}
