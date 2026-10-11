#pragma once

#include <SDL3/SDL.h>

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Math/Vector2.hpp"

class RectRenderComponent : public Component {
public:
  Vector2 size{60.0f, 60.0f};
  SDL_Color color{60, 180, 100, 255};
  SDL_Color line_color{0 , 0 , 0 , 255};
  bool line{false};
  RectRenderComponent() = default;
  explicit RectRenderComponent(Vector2 sz, SDL_Color col);
  explicit RectRenderComponent(Vector2 sz , SDL_Color col , SDL_Color lc);
  void Render(SDL_Renderer *renderer) override;

  std::unique_ptr<Component> Clone() const override;

};
