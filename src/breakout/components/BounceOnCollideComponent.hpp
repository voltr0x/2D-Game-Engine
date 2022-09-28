#if !defined(BOUNCE_ON_COLLIDE_COMPONENT_HPP)
#define BOUNCE_ON_COLLIDE_COMPONENT_HPP

#include "../../base/GenericComponent.hpp"
#include "../../base/Level.hpp"

class BounceOnCollideComponent : public GenericComponent {
 private:
  float mVx{0.0f};
  float mSpeed;
  bool left{false};
  bool up{false};

 public:
  BounceOnCollideComponent(GameObject& gameObject, float speed);

  virtual void collision(Level& level, std::shared_ptr<GameObject> obj) override;

  virtual void update(Level& level) override;
};

#endif  // BOUNCE_ON_COLLIDE_COMPONENT_HPP
