#pragma once

#include <SDL3/SDL.h>
#include "Game/GameScene.hpp"
#include "Engine/Scene.hpp"



class PauseScene : public Scene {
public:
  explicit PauseScene(SceneManager *manager , std::string name);

  void HandleEvent(const SDL_Event& event) override;
  
  void Render(SDL_Renderer *renderer) override;

};
