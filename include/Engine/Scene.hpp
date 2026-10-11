#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include "Engine/GameObject.hpp"

class SceneManager;

class Scene {
protected:
  SceneManager *m_manager{nullptr};

  std::vector<std::unique_ptr<GameObject>> m_entities;

  std::string m_name;

public:

  Scene() = default;

  explicit Scene(SceneManager *manager , std::string name);

  virtual ~Scene() = default;

  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  Scene(Scene &&) noexcept = default;
  Scene &operator=(Scene &&) noexcept = default;

  virtual void Init(){}

  virtual void Exit(){}

  virtual void HandleEvent(const SDL_Event& event){}

  virtual void Update(float dt){}

  virtual void Render(SDL_Renderer *renderer){}

  GameObject* CreateGameObject(std::string tag);
  
  std::vector<std::unique_ptr<GameObject>>& GetEntities();

};
