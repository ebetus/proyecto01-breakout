#include "Engine/Scene.hpp"
#include "Engine/SceneManager.hpp"

Scene::Scene(SceneManager *manager , std::string name) : 
  m_manager(manager),
  m_name(std::move(name)) {}

GameObject* Scene::CreateGameObject(std::string tag) {
  return (std::make_unique<GameObject>(tag)).release();
}
  
std::vector<std::unique_ptr<GameObject>>& Scene::GetEntities() {
  return m_entities;
}
