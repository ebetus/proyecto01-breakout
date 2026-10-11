#include "Game/PauseScene.hpp"

PauseScene::PauseScene(SceneManager *manager , std::string name) : Scene(manager,name){}

void PauseScene::HandleEvent(const SDL_Event& event) {
    if(event.type == SDL_EVENT_KEY_DOWN) {
        if(event.key.scancode == SDL_SCANCODE_P ||
           event.key.scancode == SDL_SCANCODE_ESCAPE) {
            m_manager->PopScene();
        }
    }
}

void PauseScene::Render(SDL_Renderer *renderer){
    // Overlay oscuro semitransparente para tapar el juego
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180); 
    
    // Ajustado a 750 de ancho por 1000 de alto
    SDL_FRect screen_overlay{0.0f, 0.0f, 750.0f, 1000.0f};
    SDL_RenderFillRect(renderer, &screen_overlay);

    // Caja pausa
    SDL_FRect pauseBox { 175.0f, 400.0f, 400.0f, 200.0f };
    SDL_SetRenderDrawColor(renderer, 30, 40, 60, 220);
    SDL_RenderFillRect(renderer, &pauseBox);

    // Texto "PAUSE"
    const char* pauseBitmap[] = {
        "XXXX  XX  X  X XXXX  XX ",
        "X  X X  X X  X X    X  X",
        "XXXX XXXX X  X XXXX XXXX",
        "X    X  X X  X    X X  X",
        "X    X  X  XX  XXXX X  X"
    };

    float pixelSize = 12.0f; 
    float startX = 231.0f;
    float startY = 470.0f;

    // Desactivamos blend para dibujar los rectángulos sólidos
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 242, 96, 34, 255);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 24; ++col) {
            if (pauseBitmap[row][col] == 'X') {
                SDL_FRect pRect = {
                    startX + col * pixelSize,
                    startY + row * pixelSize,
                    pixelSize - 1.0f, 
                    pixelSize - 1.0f
                };
                SDL_RenderFillRect(renderer, &pRect);
            }
        }
    }
}
