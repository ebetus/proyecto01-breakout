#include "Game/GameScene.hpp"
#include "Game/DesactivatorComponent.hpp"
#include "Game/LifeRenderComponent.hpp"
#include "Game/WinScene.hpp"

GameScene::GameScene(SceneManager *manager , std::string name) : Scene(manager,name){
  m_collisionManager = std::make_unique<CollisionManager>(&m_entities);
}

void GameScene::Init() {
  m_entities.clear();
  m_collisionManager->SetEntities(&m_entities);
  auto player = std::make_unique<GameObject>("Player");
  player->AddComponent<TransformComponent>(Vector2{305.0f, 875.0f},
					   Vector2{1.0f, 1.0f});
  player->AddComponent<RectRenderComponent>(Vector2{140.0f, 20.0f},
					    SDL_Color{242, 96, 34, 255});
  player->AddComponent<ColliderComponent>(Vector2{140.0f, 20.0f});
  player->AddComponent<PlayerControllerComponent>(400.0f,  m_manager);
  player->AddComponent<LifeRenderComponent>();
  GameObject* playerObject = player.get();
  m_entities.push_back(std::move(player));

   auto ball = std::make_unique<GameObject>("Ball");
  ball->AddComponent<TransformComponent>(Vector2{365.0f , 855.0f});
  ball->AddComponent<RectRenderComponent>(Vector2{20.0f, 20.0f},
					  SDL_Color{51, 34, 242, 255});
  ball->AddComponent<ColliderComponent>(Vector2{20.0f,20.0f});
  ball->AddComponent<BallComponent>(350.0f , playerObject);
  //Para que se renderice primero el jugador.
  m_entities.insert(m_entities.begin() , std::move(ball));

  //Colores para los ladrillos
  SDL_Color three_life_color = {222,209,24,255};
  SDL_Color two_life_color = {125,125,125,255};
  SDL_Color one_life_color = {139,217,199,255};
  SDL_Color line_color = {0,0,0,255};

  //Posición del comienzo
  float x = 0.0f;
  float y = 100.0f;
  
  //Primera ilera con tres vidas
  for(int i = 0 ; i < 10 ; i++) {
    auto obstacle = std::make_unique<GameObject>("Brick");
    obstacle->AddComponent<TransformComponent>(Vector2{x, y},
					       Vector2{1.0f, 1.0f});
    obstacle->AddComponent<RectRenderComponent>(Vector2{75.0f, 50.0f},
						three_life_color , line_color);
    obstacle->AddComponent<ColliderComponent>(Vector2{75.0f,50.0f});
    obstacle->AddComponent<DesactivatorComponent>(3);
    m_entities.push_back(std::move(obstacle));
    x += 75.0f;
  }
  x = 0.0f;
  y += 50.0f;
  //Segunda ilera con 2 vidas
  for(int i = 0 ; i < 10 ; i++) {
    auto obstacle = std::make_unique<GameObject>("Brick");
    obstacle->AddComponent<TransformComponent>(Vector2{x, y},
					       Vector2{1.0f, 1.0f});
    obstacle->AddComponent<RectRenderComponent>(Vector2{75.0f, 50.0f},
						two_life_color , line_color);
    obstacle->AddComponent<ColliderComponent>(Vector2{75.0f,50.0f});
    obstacle->AddComponent<DesactivatorComponent>(2);
    m_entities.push_back(std::move(obstacle));
    x += 75.0f;
  }

  x = 0.0f;
  
  y += 50.0f;

  // 4 ileras mas de una vida:
  for(int i = 0 ; i < 4 ; i++) {
    for(int j = 0 ; j < 10 ; j++) {
      auto obstacle = std::make_unique<GameObject>("Brick");
      obstacle->AddComponent<TransformComponent>(Vector2{x, y},
						 Vector2{1.0f, 1.0f});
      obstacle->AddComponent<RectRenderComponent>(Vector2{75.0f, 50.0f},
						  one_life_color , line_color);
      obstacle->AddComponent<ColliderComponent>(Vector2{75.0f,50.0f});
      obstacle->AddComponent<DesactivatorComponent>(1);
      m_entities.push_back(std::move(obstacle));
      x += 75.0f;
    }
    x = 0.0f;
    y += 50.0f;
  }
}

void GameScene::Update(float dt) {
  constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
  m_physicsAccumulator += dt;
  //FixedUpdate
  int actives{0}; //Para contar si solo queda la bola y el jugador
  while (m_physicsAccumulator >= FIXED_TIMESTEP) {
    for (auto &entity : m_entities){
      if(entity != nullptr && entity->IsActive()){
	entity->FixedUpdate(FIXED_TIMESTEP);
      }
    }
    m_collisionManager->CheckCollisions();
    m_physicsAccumulator -= FIXED_TIMESTEP;
  }
  //Update
  for(auto &entity : m_entities) {
    if(entity != nullptr && entity->IsActive()){
      entity->Update(dt);
      actives++;
    }
  }

  //Solo tendrían que estar activos el player y la pelota
  if(actives == 2) {
    m_manager->PushScene(std::move(std::make_unique<PauseScene>(m_manager , "PauseScene")));
  }
}

//Aqui va todo lo del juego.
void GameScene::HandleEvent(const SDL_Event& event) {
  if(event.type == SDL_EVENT_KEY_DOWN) {
    if(event.key.scancode == SDL_SCANCODE_F1) {
      m_debugDraw = !m_debugDraw;
    }
    if(event.key.scancode == SDL_SCANCODE_P ||
       event.key.scancode == SDL_SCANCODE_ESCAPE) {
      m_manager->PushScene(std::move(std::make_unique<PauseScene>(m_manager , "PauseScene")));
    }
    if(event.key.scancode == SDL_SCANCODE_G) {
      m_manager->ChangeScene(std::move(std::make_unique<GameOverScene>(m_manager , "GameOverScene")));
    }
  }
}

void GameScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
  SDL_RenderClear(renderer);
  for (auto &entity : m_entities)
    entity->Render(renderer);
  if (m_debugDraw) {
    for (auto &entity : m_entities) {
      if (auto *col = entity->GetComponent<ColliderComponent>()) {
	col->RenderDebug(renderer);
      }
    }
  }
}

