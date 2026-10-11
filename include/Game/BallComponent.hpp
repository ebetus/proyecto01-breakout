#pragma once

#include <cmath>
#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/GameObject.hpp"
#include <memory>

class BallComponent : public Component{
public:

  
  float m_speed{220.0f};
  
  Vector2 velocity{0 , 0};

  GameObject* playerObject;

  BallComponent() = default;
  
  explicit BallComponent(float speed);

  explicit BallComponent(float speed , GameObject* player);
  
  void FixedUpdate(float fdt);

  void OnCollisionEnter(GameObject *other);

  std::unique_ptr<Component> Clone() const override;
};
