#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Engine/Scene.hpp"


enum class SceneAction {
  None,
  Change,
  Push,
  Pop,
  Clear
};

class SceneManager {

private:
  std::vector<std::unique_ptr<Scene>> m_scenes;
  
  SceneAction m_pendingAction{SceneAction::None};
  
  std::unique_ptr<Scene> m_pendingScene{nullptr};

  void popSceneFromScenes();

  void transferPendingScene();

public:
  void ChangeScene(std::unique_ptr<Scene> new_scene);

  void PushScene(std::unique_ptr<Scene> new_scene);

  void PopScene();

  void Clear();

  void ProcessPendingChanges();

  void HandleEvent(const SDL_Event &event);

  void Update(float dt);

  void Render(SDL_Renderer *renderer);

  bool HasScenes();

};
