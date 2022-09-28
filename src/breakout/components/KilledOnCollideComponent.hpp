#if !defined(KILLED_ON_COLLIDECOMPONENT_HPP)
#define KILLED_ON_COLLIDECOMPONENT_HPP

#include "../../base/GenericComponent.hpp"
#include "../../base/Level.hpp"

class KilledOnCollideComponent : public GenericComponent {
 private:
  int mTag;

 public:
  KilledOnCollideComponent(GameObject& gameObject, int tag);

  void collision(Level& level, std::shared_ptr<GameObject> obj) override;
};

#endif  // KILLED_ON_COLLIDECOMPONENT_HPP
