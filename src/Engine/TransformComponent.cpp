#include "Engine/TransformComponent.hpp"

TransformComponent::TransformComponent(Vector2 pos) : position(pos) {}
TransformComponent::TransformComponent(Vector2 pos, Vector2 scl) : position(pos), scale(scl) {}

void TransformComponent::Translate(const Vector2 &offset) {
  position = position + offset;
}

std::unique_ptr<Component> TransformComponent::Clone() const {
  return std::make_unique<TransformComponent>(*this);
}
