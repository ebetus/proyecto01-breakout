#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"

class LifeRenderComponent : public Component {
public:

  LifeRenderComponent() = default;

  std::unique_ptr<Component> Clone() const override;

  void Render(SDL_Renderer *renderer);
};
