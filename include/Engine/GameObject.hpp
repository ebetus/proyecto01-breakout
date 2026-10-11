#pragma once

#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <SDL3/SDL.h>

#include "Engine/Component.hpp"

class GameObject {

private:
  std::vector<std::unique_ptr<Component>> m_components;
  std::string m_tag{"GameObject"};
  bool m_active{true};

public:
  GameObject() = default;
  explicit GameObject(std::string tag);
  ~GameObject() = default;

  // Deshabilitar copia para garantizar la propiedad estricta de unique ptr
  GameObject(const GameObject &) = delete;
  GameObject &operator=(const GameObject &) = delete;
  
  // Habilitar movimiento en memoria
  GameObject(GameObject &&) noexcept = default;
  GameObject &operator=(GameObject &&) noexcept = default;
  
  // Identificación y estado
  const std::string &GetTag() const;
  void SetTag(std::string tag);
  bool IsActive() const;
  void SetActive(bool active);

  //Para armar componentes con reenvio perfecto
  template <typename T, typename... Args>
  T *AddComponent(Args &&...args) {
    static_assert(std::is_base_of_v<Component, T>, "T debe derivar de Component");

    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->owner = this;
    component->Init();
    T *ptr = component.get();
    m_components.push_back(std::move(component));
    return ptr;
  }

  // Consulta de componentes
  template <typename T>
  T *GetComponent() const {
    static_assert(std::is_base_of_v<Component, T>, "T debe derivar de Component");

    for (const auto &component : m_components) {
      if (auto casted = dynamic_cast<T *>(component.get()))
	return casted;
    }
    return nullptr;
  }

  template <typename T>
  bool HasComponent() const {
    return GetComponent<T>() != nullptr;
  }

  void Update(float dt);

  void FixedUpdate(float fdt);

  void Render(SDL_Renderer *renderer);

  void OnCollision(GameObject *other);

  void OnCollisionEnter(GameObject *other);

  void OnCollisionStay(GameObject *other);

  void OnCollisionExit(GameObject *other);

  std::unique_ptr<GameObject> Clone() const;
};
