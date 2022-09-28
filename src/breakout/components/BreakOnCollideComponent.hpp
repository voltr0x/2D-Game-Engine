#ifndef BREAK_ON_COLLIDE_COMPONENT
#define BREAK_ON_COLLIDE_COMPONENT

#include "../../base/GenericComponent.hpp"
#include "../../base/Level.hpp"

//! \brief A component that removes a game object (of a given tag) on collision.
class BreakOnCollideComponent : public GenericComponent {
 public:
  BreakOnCollideComponent(GameObject& gameObject, int tag);

  virtual void collision(Level& level, std::shared_ptr<GameObject> obj) override;

  virtual void update(Level& level) override;

 private:
  int mTag;
};

#endif  // BREAK_ON_COLLIDE_COMPONENT
