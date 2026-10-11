#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"

class DesactivatorComponent : public Component {
public:

  DesactivatorComponent() = default;
  explicit DesactivatorComponent(int l);
  std::unique_ptr<Component> Clone() const override;
  void OnCollisionEnter(GameObject* other) override;

private:
  int m_life{1};
};
