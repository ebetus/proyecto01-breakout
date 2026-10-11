#pragma once

#include <SDL3/SDL.h>
#include <memory>

class GameObject;

class Component {
public:
  // Puntero de vuelta al padre
  GameObject *owner{nullptr};
  // Destructor virtual
  virtual ~Component() = default;

  // Métodos virtuales del ciclo de vida
  virtual void Init();
  virtual void Update(float dt);
  virtual void FixedUpdate(float fdt){};
  virtual void Render(SDL_Renderer *renderer);
  virtual void OnCollision(GameObject *other);
  virtual void OnCollisionEnter(GameObject *other){}
  virtual void OnCollisionStay(GameObject *other){}
  virtual void OnCollisionExit(GameObject *other){}
  virtual std::unique_ptr<Component> Clone() const = 0;
};
