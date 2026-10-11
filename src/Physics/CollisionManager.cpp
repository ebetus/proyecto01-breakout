#include "Physics/CollisionManager.hpp"
  
CollisionManager::CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities)
  : m_entities{entities}{}

CollisionManager::CollisionPair CollisionManager::MakePair(GameObject* a,
							   GameObject* b) {
  return CollisionPair(a , b);
}
 

void CollisionManager::SetEntities(std::vector<std::unique_ptr<GameObject>> *entities) {
  m_entities = std::move(entities);
}
  
bool CollisionManager::CheckAABB(const SDL_FRect &a , const SDL_FRect &b){
  return (a.x < b.x + b.w &&
	  a.x + a.w > b.x &&
	  a.y < b.y + b.h &&
	  a.y + a.h > b.y);
}

bool CollisionManager::CheckCollision(const ColliderComponent &a , const ColliderComponent &b) {
  return CheckAABB(a.GetWorldBounds(), b.GetWorldBounds());
}

void CollisionManager::CheckCollisions() {
  auto &entities = *m_entities;
  
  //Limpieza del frame anterior
  m_current.clear();
  for(auto &entity : entities) {
    ColliderComponent* c = entity->GetComponent<ColliderComponent>();
    if(c != nullptr)
      c->is_colliding = false;
  }

  
  for(size_t i = 0 ; i < entities.size() ; i++) {
    ColliderComponent* colA = entities[i]->GetComponent<ColliderComponent>();
    if(colA == nullptr || !entities[i]->IsActive())
      continue;
    
    for(size_t j = i+1 ; j < entities.size() ; j++){
      ColliderComponent* colB = entities[j]->GetComponent<ColliderComponent>();
      if(colB == nullptr || !entities[j]->IsActive())
	continue;
      
      bool colliding = CheckCollision(*colA, *colB);
      if(colliding){
	colA->is_colliding = colliding;
	colB->is_colliding = colliding;
	m_current.insert(MakePair(entities[i].get() , entities[j].get()));
	  
      }
    }
  }

  std::vector<CollisionPair> enters , stays , exits;

  for(const auto&p : m_current) {
    if(m_previous.count(p))
      stays.push_back(p);
    else
      enters.push_back(p);
  }

  for(const auto&p : m_previous) {
    if(!m_current.count(p))
      exits.push_back(p);
  }

  for(const auto&p : enters) Dispatch(p, Phase::Enter);
  for(const auto&p : stays) Dispatch(p, Phase::Stay);
  for(const auto&p : exits) Dispatch(p, Phase::Exit);

  m_previous = m_current;
}


void CollisionManager::Dispatch(const CollisionPair &pair , Phase phase) {

  GameObject *a = pair.entityA;
  GameObject *b = pair.entityB;

  auto *colA = a->GetComponent<ColliderComponent>();
  auto *colB = b->GetComponent<ColliderComponent>();

  const bool trigger = (colA && colA->is_trigger) || (colB && colB->is_trigger);

  switch(phase) {
  case Phase::Enter:
    a->OnCollisionEnter(b);
    b->OnCollisionEnter(a);
    break;
  case Phase::Stay:
    a->OnCollisionStay(b);
    b->OnCollisionStay(a);
    break;
  case Phase::Exit:
    a->OnCollisionExit(b);
    b->OnCollisionExit(a);
    break;
  }

  if(phase != Phase::Exit){
    a->OnCollision(b);
    b->OnCollision(a);
  }
}






