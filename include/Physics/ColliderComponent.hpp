#pragma once
#include <SDL3/SDL.h>
#include "Math/Vector2.hpp"
#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"

class ColliderComponent : public Component {
public:

  //Desplazamiento relativo a la posicion del TransformComponent
  Vector2 offset{0.0f,0.0f};

  //El tamaño del collider
  Vector2 size{60.0f,60.0f};

  //Marca si es un sensor sin fisica
  bool is_trigger{false};

  //Marca si esta tocando con otro collider
  bool is_colliding{false};

  explicit ColliderComponent(Vector2 size);


  SDL_FRect GetWorldBounds() const;

  void RenderDebug(SDL_Renderer *renderer);

  std::unique_ptr<Component> Clone() const override;
};
