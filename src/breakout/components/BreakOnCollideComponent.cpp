#include "BreakOnCollideComponent.hpp"
#include "../../Globals.hpp"

BreakOnCollideComponent::BreakOnCollideComponent(GameObject& gameObject, int tag)
    : GenericComponent(gameObject),
      mTag(tag) {
}

void BreakOnCollideComponent::collision(Level& level, std::shared_ptr<GameObject> obj) {
  // current object
  // GameObject& gameObject = getGameObject();

  if (obj->tag() == mTag && level.state() == STATE_RUNING) {
    level.removeObject(obj);
    // TODO set bricks with different score
    level.collecting(1);
  }
}

void BreakOnCollideComponent::update(Level& level) {
  // check if all bricks have been removed
  // std::vector<std::shared_ptr<GameObject>> allObjects = level.getAllObjects();
  bool levelCleared = true;
  for (auto gameObject : level.getAllObjects()) {
    // TODO refactor to resetables
    if (gameObject->tag() == mTag) {
      levelCleared = false;
      break;
    }
  }
  if (levelCleared) {
    level.nextLevel();
  }
}