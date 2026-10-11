#include "Game/GameOverScene.hpp"
#include "Game/GameScene.hpp"
#include "Game/TitleScene.hpp"

GameOverScene::GameOverScene(SceneManager *manager , std::string name) : Scene(manager,name) {}

void GameOverScene::HandleEvent(const SDL_Event& event) {
  SDL_FRect btnRestart = { 275.0f, 650.0f, 200.0f, 60.0f };
  SDL_FRect btnMenu    = { 275.0f, 750.0f, 200.0f, 60.0f };

  switch (event.type) {
  case SDL_EVENT_KEY_DOWN:
    if (event.key.scancode == SDL_SCANCODE_R) {
      m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
    } 
    else if (event.key.scancode == SDL_SCANCODE_M) {
      m_manager->ChangeScene(std::move(std::make_unique<TitleScene>(m_manager , "TitleScene")));
    }
    break;

  case SDL_EVENT_MOUSE_BUTTON_DOWN: {
    if (event.button.button == SDL_BUTTON_LEFT) {
      float mx = event.button.x;
      float my = event.button.y;
      //Click simple en el boton de reiniciar
      if (mx >= btnRestart.x && mx <= (btnRestart.x + btnRestart.w) &&
	  my >= btnRestart.y && my <= (btnRestart.y + btnRestart.h)) {
	m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
      }
      //Clic simple en el boton de menú
      if (mx >= btnMenu.x && mx <= (btnMenu.x + btnMenu.w) &&
	  my >= btnMenu.y && my <= (btnMenu.y + btnMenu.h)) {
	m_manager->ChangeScene(std::move(std::make_unique<TitleScene>(m_manager , "TitleScene")));
      }
    }
    break;
  }
  }
}

void GameOverScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 10, 10, 15, 255);
  SDL_RenderClear(renderer);

  const char* gameBitmap[] = {
    " XXX   X   X X XXXX",
    "X     X X  XXX X   ",
    "X XX XXXXX X X XXX ",
    "X  X X   X X X X   ",
    " XXX X   X X X XXXX"
  };

  const char* overBitmap[] = {
    " XX  X   X XXXX XXX ",
    "X  X X   X X    X  X",
    "X  X X   X XXX  XXX ",
    "X  X  X X  X    X  X",
    " XX    X   XXXX X  X"
  };

  float pixelSize = 18.0f; 
  float startX = 195.0f;
  float startY_Game = 200.0f;
  float startY_Over = 320.0f;

  SDL_SetRenderDrawColor(renderer, 220, 30, 30, 255);

  for (int row = 0; row < 5; ++row) {
    for (int col = 0; col < 20; ++col) {
      if (gameBitmap[row][col] == 'X') {
	SDL_FRect pRect = { startX + col * pixelSize, startY_Game + row * pixelSize, pixelSize - 1.0f, pixelSize - 1.0f };
	SDL_RenderFillRect(renderer, &pRect);
      }
    }
  }

  for (int row = 0; row < 5; ++row) {
    for (int col = 0; col < 20; ++col) {
      if (overBitmap[row][col] == 'X') {
	SDL_FRect pRect = { startX + col * pixelSize, startY_Over + row * pixelSize, pixelSize - 1.0f, pixelSize - 1.0f };
	SDL_RenderFillRect(renderer, &pRect);
      }
    }
  }

  SDL_FRect btnRestart = { 275.0f, 650.0f, 200.0f, 60.0f };
    
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderFillRect(renderer, &btnRestart);
    
  SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
  SDL_RenderRect(renderer, &btnRestart);

  const char* restartIcon[] = {
    "XX ",
    "X X",
    "XX ",
    "X X",
    "X X"
  };
    
  float iconPixel = 6.0f;
  float iconX = btnRestart.x + 91.0f;
  float iconY = btnRestart.y + 15.0f;
    
  SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 3; ++c) {
      if (restartIcon[r][c] == 'X') {
	SDL_FRect iRect = { iconX + c * iconPixel, iconY + r * iconPixel, iconPixel, iconPixel };
	SDL_RenderFillRect(renderer, &iRect);
      }
    }
  }

  SDL_FRect btnMenu = { 275.0f, 750.0f, 200.0f, 60.0f };
    
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderFillRect(renderer, &btnMenu);
    
  SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
  SDL_RenderRect(renderer, &btnMenu);

  const char* menuIcon[] = {
    "X   X",
    "XX XX",
    "X X X",
    "X   X",
    "X   X"
  };
    
  float mIconX = btnMenu.x + 85.0f;
  float mIconY = btnMenu.y + 15.0f;
    
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 5; ++c) {
      if (menuIcon[r][c] == 'X') {
	SDL_FRect iRect = { mIconX + c * iconPixel, mIconY + r * iconPixel, iconPixel, iconPixel };
	SDL_RenderFillRect(renderer, &iRect);
      }
    }
  }
}
