#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <set>
#include "Engine/Component.hpp"
#include "Physics/ColliderComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"

class CollisionManager {
public:

  std::vector<std::unique_ptr<GameObject>> *m_entities{nullptr};
  
  explicit CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities);
  
  void SetEntities(std::vector<std::unique_ptr<GameObject>> *entities);
  
  bool CheckAABB(const SDL_FRect &a , const SDL_FRect &b);

  bool CheckCollision(const ColliderComponent &a , const ColliderComponent &b);

  void CheckCollisions();

private:
  struct CollisionPair {

    GameObject* entityA{nullptr};
    GameObject* entityB{nullptr};

    CollisionPair(GameObject* a , GameObject* b) {
      if(a<b){
	entityA = a;
	entityB = b;
      }else {
	entityA = b;
	entityB = a;
      }
    }

    auto operator<=>(const CollisionPair &) const = default;
  };

  enum class Phase {
    Enter,
    Stay,
    Exit
  };

  static CollisionPair MakePair(GameObject* a , GameObject* b);
  void Dispatch(const CollisionPair &pair , Phase phase);

  std::set<CollisionPair> m_previous;
  std::set<CollisionPair> m_current;
  
};

