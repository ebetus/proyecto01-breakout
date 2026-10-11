#include "Game/BallComponent.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Physics/ColliderComponent.hpp"
#include "Game/PlayerControllerComponent.hpp"
#include <string>

BallComponent::BallComponent(float speed) : m_speed(speed) {
  float exit_angle = 3.14f/4.0f;
  velocity.x = speed * std::sin(exit_angle);
  velocity.y = -speed * std::cos(exit_angle);
}

BallComponent::BallComponent(float speed , GameObject* player)  : m_speed(speed) , playerObject(player) {
  float exit_angle = 3.14f/4.0f;
  velocity.x = speed * std::sin(exit_angle);
  velocity.y = -speed * std::cos(exit_angle);
}

void BallComponent::FixedUpdate(float dt){
  
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if(transform == nullptr)
    return;
  transform->Translate(velocity*dt);
  if(transform->position.x  <= 0){
    velocity.x = std::abs(velocity.x);
  }
  if((transform->position + (transform->scale * 0.5)).x >= 750) {
    velocity.x = -std::abs(velocity.x);
  }
  if(transform->position.y <= 0){
    velocity.y = std::abs(velocity.y);
  }
  if((transform->position + (transform->scale * 0.5)).y >= 1000) {
    velocity.y = -std::abs(velocity.y);
  }

  if(transform->position.y > 1000){
    transform->position = Vector2{365.0f, 855.0f};
    velocity.y = -std::abs(velocity.y);
    if(playerObject){
      auto *control = playerObject->GetComponent<PlayerControllerComponent>();
      control->LoseLife();
    }
    
  }
  
}

void BallComponent::OnCollisionEnter(GameObject *other) {
  if(!other || !owner)
    return;

  auto *transform = owner->GetComponent<TransformComponent>();
  auto *collider = owner->GetComponent<ColliderComponent>();
  auto *other_transform = other->GetComponent<TransformComponent>();
  auto *other_collider = other->GetComponent<ColliderComponent>();
  
  if(!transform || !collider || !other_transform || !other_collider) return;
  
  SDL_FRect ballBounds = collider->GetWorldBounds();
  SDL_FRect otherBounds = other_collider->GetWorldBounds();
  
  std::string otherTag = other->GetTag(); 

  if (otherTag == "Player") {
    // Se encuentra el centro de la pelota y el centro de la plataforma
    float ballCenter = transform->position.x + ballBounds.w;
    float playerCenter = other_transform->position.x + otherBounds.w;
        
    // Se calcula en qué punto golpeó relativo al centro
    float hit = (ballCenter - playerCenter) / (other_transform->scale.x / 2.0f);
        
    // Se mantiene entre -1 y 1
    hit = std::max(-1.0f, std::min(1.0f, hit));

    float maxAngle = 3.14f / 5.0f; // 36 grados en radianes
    float hitAngle = hit * maxAngle;
    
    velocity.x = m_speed * std::sin(hitAngle);
    velocity.y = -m_speed * std::cos(hitAngle);
    
    //Cada golpe en la plataforma va a aumentar la velocidad en 20
    if(m_speed <= 1000)
      m_speed += 25;
    //Evitar que atraviese la plataforma
    transform->position.y = otherBounds.y - ballBounds.h - 0.5f;
     
  } // 2. REBOTE CON LOS BLOQUES (A prueba de colisiones múltiples)
    else if (otherTag == "Brick") {
        float overlapLeft = (ballBounds.x + ballBounds.w) - otherBounds.x;
        float overlapRight = (otherBounds.x + otherBounds.w) - ballBounds.x;
        float overlapTop = (ballBounds.y + ballBounds.h) - otherBounds.y;
        float overlapBottom = (otherBounds.y + otherBounds.h) - ballBounds.y;

        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        if (minOverlapX < minOverlapY) {
            // Chocó por los lados
            if (overlapLeft < overlapRight) {
                // Golpeó la cara izquierda del bloque 
                velocity.x = -std::abs(velocity.x); 
                transform->position.x -= minOverlapX; // Empujar a la izquierda
            } else {
                // Golpeó la cara derecha del bloque
                velocity.x = std::abs(velocity.x); 
                transform->position.x += minOverlapX; // Empujar a la derecha
            }
        } else {
            // Chocó por arriba o abajo
            if (overlapTop < overlapBottom) {
                // Golpeó la cara superior del bloque 
                velocity.y = -std::abs(velocity.y); 
                transform->position.y -= minOverlapY; // Empujar hacia arriba
            } else {
                // Golpeó la cara inferior del bloque 
                velocity.y = std::abs(velocity.y); 
                transform->position.y += minOverlapY; // Empujar hacia abajo
            }
        }
    }
}

std::unique_ptr<Component> BallComponent::Clone() const {
  return std::make_unique<BallComponent>(*this);
}
