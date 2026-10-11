#include "Game/DesactivatorComponent.hpp"

DesactivatorComponent::DesactivatorComponent(int l) : m_life(l) {}

std::unique_ptr<Component> DesactivatorComponent::Clone() const {
  return std::make_unique<DesactivatorComponent>(*this);
}

void DesactivatorComponent::OnCollisionEnter(GameObject* other) {
  if(!other || !owner)
    return;
  m_life--;
  if(m_life <= 0)
    owner->SetActive(false);
}
