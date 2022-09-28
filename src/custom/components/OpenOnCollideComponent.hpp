#ifndef OPERN_ON_COLLIDE_COMPONENT_HPP
#define OPERN_ON_COLLIDE_COMPONENT_HPP

#include "base/GenericComponent.hpp"

//! \brief A component that collect a game object (of a given tag) on collision.
class OpenOnCollideComponent: public GenericComponent {
public:

  OpenOnCollideComponent(GameObject & gameObject, int tag);
  
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:

  int mTag;
  
};

#endif // OPERN_ON_COLLIDE_COMPONENT_HPP
