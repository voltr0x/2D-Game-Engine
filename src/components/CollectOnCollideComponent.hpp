#ifndef BASE_COLLECT_ON_COLLIDE_COMPONENT_HPP
#define BASE_COLLECT_ON_COLLIDE_COMPONENT_HPP

#include "base/GenericComponent.hpp"

//! \brief A component that collect a game object (of a given tag) on collision.
class CollectOnCollideComponent: public GenericComponent {
public:

  CollectOnCollideComponent(GameObject & gameObject, int tag);
  
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:

  int mTag;
  
};

class AttackComponent: public GenericComponent {
public:

  AttackComponent(GameObject & gameObject, int tag);
  
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:

  int mTag;
  
};
#endif // BASE_COLLECT_ON_COLLIDE_COMPONENT_HPP
