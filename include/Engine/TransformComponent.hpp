#pragma once

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"
class TransformComponent : public Component {
public:
  Vector2 position{0.0f, 0.0f};
  Vector2 scale{1.0f, 1.0f};

  TransformComponent() = default;
  explicit TransformComponent(Vector2 pos);
  TransformComponent(Vector2 pos, Vector2 scl);

  void Translate(const Vector2 &offset);

  std::unique_ptr<Component> Clone() const override;
};
