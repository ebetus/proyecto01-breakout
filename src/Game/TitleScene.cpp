#include "Game/TitleScene.hpp"
#include "Game/GameScene.hpp"

TitleScene::TitleScene(SceneManager *manager , std::string name) : Scene(manager,name) {}

void TitleScene::HandleEvent(const SDL_Event& event) {
    SDL_FRect btn = { 275.0f, 750.0f, 200.0f, 60.0f };

    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            if (event.key.scancode == SDL_SCANCODE_SPACE || 
                event.key.scancode == SDL_SCANCODE_RETURN) {
                m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            if (event.button.button == SDL_BUTTON_LEFT) {
                float mx = event.button.x;
                float my = event.button.y;
                
                // Clic simple en el botón
                if (mx >= btn.x && mx <= (btn.x + btn.w) &&
                    my >= btn.y && my <= (btn.y + btn.h)) {
                    m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
                }
            }
            break;
        }
    }
}

void TitleScene::Render(SDL_Renderer *renderer) {
    // Fondo principal
    SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
    SDL_RenderClear(renderer);

    // Título "BREAKOUT"
    const char* titleBitmap[] = {
        "XXXX XXXX XXXX  XX  X  X  XX  X  X XXXX",
        "X  X X  X X    X  X X X  X  X X  X   X ",
        "XXXX XXXX XXX  XXXX XX   X  X X  X   X ",
        "X  X X X  X    X  X X X  X  X X  X   X ",
        "XXXX X  X XXXX X  X X  X  XX   XX    X "
    };

    float pixelSize = 15.0f;
    float startX = 82.5f; 
    float startY = 250.0f;

    // Gris claro para todo el texto
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 39; ++col) {
            if (titleBitmap[row][col] == 'X') {
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
    

    // Plataforma
    SDL_SetRenderDrawColor(renderer, 242, 96, 34, 255);
    SDL_FRect paddle = { 305.0f, 550.0f, 140.0f, 20.0f };
    SDL_RenderFillRect(renderer, &paddle);

    // Pelota
    SDL_SetRenderDrawColor(renderer, 51, 34, 242, 255);
    SDL_FRect ball = { 365.0f, 530.0f, 20.0f, 20.0f };
    SDL_RenderFillRect(renderer, &ball);

    // Botón de Iniciar
    SDL_SetRenderDrawColor(renderer, 65, 117, 39, 255);
    SDL_FRect btnRect = { 275.0f, 750.0f, 200.0f, 60.0f };
    SDL_RenderFillRect(renderer, &btnRect);

    // Triángulo de Play
    SDL_Vertex vertices[3];
    vertices[0].position = { 360.0f, 765.0f };
    vertices[0].color    = { 0, 0, 0, 255 };
    
    vertices[1].position = { 360.0f, 795.0f };
    vertices[1].color    = { 0, 0, 0, 255 };
    
    vertices[2].position = { 390.0f, 780.0f };
    vertices[2].color    = { 0, 0, 0, 255 };

    int indices[3] = { 0, 1, 2 };
    SDL_RenderGeometry(renderer, nullptr, vertices, 3, indices, 3);
}
