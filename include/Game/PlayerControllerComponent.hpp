#pragma once

#include <SDL3/SDL.h>

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"
#include "Math/Vector2.hpp"
#include "Engine/SceneManager.hpp"


class PlayerControllerComponent : public Component {
public:
  float speed{300.0f};
  SceneManager* sceneManager;
  int lifes{3};

  PlayerControllerComponent() = default;
  explicit PlayerControllerComponent(float spd, SceneManager* sceneManager);
  void Update(float dt) override;
  std::unique_ptr<Component> Clone() const override;
  void LoseLife();
};
