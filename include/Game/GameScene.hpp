#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "Engine/Scene.hpp"
#include "Game/PauseScene.hpp"
#include "Game/GameOverScene.hpp"
#include "Math/Vector2.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"
#include "Game/PlayerControllerComponent.hpp"
#include "Physics/CollisionManager.hpp"
#include "Game/BallComponent.hpp"
#include "Engine/SceneManager.hpp"

class GameScene : public Scene {
private:
  std::unique_ptr<CollisionManager> m_collisionManager;
  float m_physicsAccumulator{0.0f};
  bool m_debugDraw{false};

public:

  GameScene() = default;
  
  explicit GameScene(SceneManager *manager , std::string name);

  void Init() override;

  void Update(float dt) override;

  void HandleEvent(const SDL_Event& event) override;

  void Render(SDL_Renderer *renderer) override;
};
