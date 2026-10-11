#include "Game/LifeRenderComponent.hpp"
#include "Game/PlayerControllerComponent.hpp"

std::unique_ptr<Component> LifeRenderComponent::Clone() const {
  return std::make_unique<LifeRenderComponent>(*this);
}

void LifeRenderComponent::Render(SDL_Renderer *renderer) {
  PlayerControllerComponent* pc = owner->GetComponent<PlayerControllerComponent>();
  if(!pc) return;
  int lifes = pc->lifes;


  SDL_SetRenderDrawColor(renderer, 20, 87, 120,255);
  SDL_FRect backGround{0.0f , 910.0f , 750.0f , 100.0f};
  SDL_RenderFillRect(renderer, &backGround);

  //Depende de las vidas dibuja "Las vidas restantes"
  SDL_SetRenderDrawColor(renderer, 242, 96, 34,255);
  float x = 10.0f;
  float y = 950.0f;
  SDL_FRect rect1{x , y , 140.0f , 20.0f};
  SDL_FRect rect2{x+150 , y , 140.0f, 20.0f};
  switch(lifes) {
  case 3:
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    break;
  case 2:
    SDL_RenderFillRect(renderer, &rect1);
    break;
  default:
    break;
  }
}
