#include "Engine/RectRenderComponent.hpp"

RectRenderComponent::RectRenderComponent(Vector2 sz, SDL_Color col) : size(sz), color(col){}

RectRenderComponent::RectRenderComponent(Vector2 sz,
					 SDL_Color col ,
					 SDL_Color lc) : size(sz),
							 color(col),
							 line_color(lc),
							 line(true){}

void RectRenderComponent::Render(SDL_Renderer *renderer){
  if (!owner) return;
    
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return; // No podemos renderizar si la entidad no tiene posicion en el mundo


  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,color.a);

  SDL_FRect rect{
    transform->position.x,
    transform->position.y,
    size.x * transform->scale.x,
    size.y * transform->scale.y
    
  };
  SDL_RenderFillRect(renderer, &rect);

  if(line) {
    SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g, line_color.b,line_color.a);
    SDL_RenderRect(renderer , &rect);
  }

}

std::unique_ptr<Component> RectRenderComponent::Clone() const{
  return std::make_unique<RectRenderComponent>(*this);
}

