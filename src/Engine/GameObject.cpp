#include "Engine/GameObject.hpp"


GameObject::GameObject(std::string tag) : m_tag(std::move(tag)) {}

  
// Identificación y estado
const std::string& GameObject::GetTag() const { return m_tag; }
void GameObject::SetTag(std::string tag) { m_tag = std::move(tag); }
bool GameObject::IsActive() const { return m_active; }
void GameObject::SetActive(bool active) { m_active = active; }


// Propagación del ciclo de vida a todos los componentes hijos
void GameObject::Update(float dt) {
  if (!m_active) return;
  for (auto &component : m_components)
    component->Update(dt);
}

void GameObject::FixedUpdate(float fdt) {
  if (!m_active) return;
  for (auto &component : m_components)
    component->FixedUpdate(fdt);
}

void GameObject::Render(SDL_Renderer *renderer) {
  if (!m_active) return;
  for (auto &component : m_components)
    component->Render(renderer);
}

void GameObject::OnCollision(GameObject *other) {
  if(!m_active) return;
  for(auto &component : m_components)
    component->OnCollision(other);
}

void GameObject::OnCollisionEnter(GameObject *other) {
  if(!m_active) return;
  for(auto &component : m_components)
    component->OnCollisionEnter(other);
}

void GameObject::OnCollisionStay(GameObject *other) {
  if(!m_active) return;
  for(auto &component : m_components)
    component->OnCollisionStay(other);
}

void GameObject::OnCollisionExit(GameObject *other) {
  if(!m_active) return;
  for(auto &component : m_components)
    component->OnCollisionExit(other);
}

std::unique_ptr<GameObject> GameObject::Clone() const {
  const std::string &new_tag = "ObjectClone";
  auto cloned_object = std::make_unique<GameObject>(new_tag);
  cloned_object->SetActive(IsActive());

  for(const auto &comp : m_components) {
    if(comp){
      auto cloned_comp = comp->Clone();
      cloned_comp->owner = cloned_object.get();
      cloned_object->m_components.push_back(std::move(cloned_comp));
    }
  }
  return cloned_object;
  
}
