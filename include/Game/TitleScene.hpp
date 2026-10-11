#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "Game/GameScene.hpp"
#include "Engine/Scene.hpp"



class TitleScene : public Scene {

public:
  
  TitleScene() = default;

  explicit TitleScene(SceneManager *manager , std::string name);

  void HandleEvent(const SDL_Event& event) override;
  
  void Render(SDL_Renderer *renderer) override;

private:
  bool m_isHovered{false};

};
