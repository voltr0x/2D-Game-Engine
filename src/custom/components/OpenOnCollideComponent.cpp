#include "OpenOnCollideComponent.hpp"
#include "base/Level.hpp"
#include "Globals.hpp"

/**
 * Starts up the component.
 */
OpenOnCollideComponent::OpenOnCollideComponent(GameObject& gameObject, int tag)
    : GenericComponent(gameObject),
      mTag(tag) {
}

/**
 * Removes the object based on the object tag and if there are still objects left in the level.
 */
void OpenOnCollideComponent::collision(Level& level, std::shared_ptr<GameObject> obj) {
  if (obj->tag() == mTag) {
      if(level.collection() > 0){
          level.decrementCollection();
          level.removeObject(obj);
      }
  }
}
