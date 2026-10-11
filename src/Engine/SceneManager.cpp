#include "Engine/SceneManager.hpp"



void SceneManager::popSceneFromScenes() {
  
  if(m_scenes.size() != 0){
    auto &scene = m_scenes.back();
    m_scenes.pop_back();
    if(scene != nullptr)
      scene->Exit();
    
  }
}

void SceneManager::transferPendingScene() {
  
  if(m_pendingScene != nullptr){
    m_pendingScene->Init();
    m_scenes.push_back(std::move(m_pendingScene));
  }
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> new_scene) {
  m_pendingAction = SceneAction::Change;
  m_pendingScene = std::move(new_scene);
}

void SceneManager::PushScene(std::unique_ptr<Scene> new_scene) {
  m_pendingAction = SceneAction::Push;
  m_pendingScene = std::move(new_scene);
}

void SceneManager::PopScene() {
  m_pendingAction = SceneAction::Pop;
}

void SceneManager::Clear() {
  //Sacar escenas y ejecutar exit
  while(m_scenes.size() != 0) {
    popSceneFromScenes();
  }
}

void SceneManager::ProcessPendingChanges() {
  
  switch(m_pendingAction) {
  case SceneAction::None:
    return;
  case SceneAction::Change:
    popSceneFromScenes();
    transferPendingScene();
    break;
  case SceneAction::Push:
    transferPendingScene();
    break;
  case SceneAction::Pop:
    popSceneFromScenes();
    break;
  case SceneAction::Clear:
    Clear();
    break;
  }
  m_pendingAction = SceneAction::None;
  m_pendingScene.reset();
}

void SceneManager::HandleEvent(const SDL_Event &event) {
  if(m_scenes.size() != 0) {
    m_scenes.back()->HandleEvent(event);
  }
}

void SceneManager::Update(float dt) {
  if(m_scenes.size() != 0) {
    m_scenes.back()->Update(dt);
  }
}

void SceneManager::Render(SDL_Renderer *renderer) {
  for(auto &scene : m_scenes){
    scene->Render(renderer);
  }
}

bool SceneManager::HasScenes() {
  return m_scenes.size() != 0;
}

