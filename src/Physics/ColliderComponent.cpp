#include "Physics/ColliderComponent.hpp"


ColliderComponent::ColliderComponent(Vector2 size): size(size){}


SDL_FRect ColliderComponent::GetWorldBounds() const {
  if(owner == nullptr)
    return {offset.x,offset.y,size.x,size.y};
  TransformComponent* transform = owner->GetComponent<TransformComponent>();
  if(transform == nullptr)
    return {offset.x,offset.y,size.x,size.y};
  float x = transform->position.x + (offset.x * transform->scale.x);
  float y = transform->position.y + (offset.y * transform->scale.y);
  float w = size.x * transform->scale.x;
  float h = size.y * transform->scale.y;
  return {x,y,w,h};
}

void ColliderComponent::RenderDebug(SDL_Renderer *renderer) {
  auto bounds = GetWorldBounds();
  if(is_colliding)
    SDL_SetRenderDrawColor(renderer, 255, 50, 50 ,255);
  else
    SDL_SetRenderDrawColor(renderer, 20, 255, 50 ,255);
  SDL_RenderRect(renderer, &bounds);
}

std::unique_ptr<Component> ColliderComponent::Clone() const {
  return std::make_unique<ColliderComponent>(*this);
}

