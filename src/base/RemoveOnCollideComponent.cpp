#include "base/RemoveOnCollideComponent.hpp"
#include "../Globals.hpp"
#include "base/Level.hpp"

RemoveOnCollideComponent::RemoveOnCollideComponent(GameObject& gameObject, int tag)
    : GenericComponent(gameObject),
      mTag(tag) {
}

void RemoveOnCollideComponent::collision(Level& level, std::shared_ptr<GameObject> obj) {
  // current object
  // GameObject& gameObject = getGameObject();

  if (obj->tag() == mTag && level.state() == STATE_RUNING) {
    
    if (obj->tag() == TAG_PLAYER && level.state() != STATE_KILLED) {
      /* killed */
      std::cout << "Got kill: state: " << level.state() << std::endl;
      if (level.getLastInvincible() == -1) {
        obj->setX(obj->x() - 100);
        obj->setDown(true);
        obj->die(true);
        level.setState(STATE_KILLED);
      }
    } else {
      level.removeObject(obj);
    }
  }
}
