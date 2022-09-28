#include "KilledOnCollideComponent.hpp"
#include "../../Globals.hpp"

KilledOnCollideComponent::KilledOnCollideComponent(GameObject& gameObject, int tag)
    : GenericComponent(gameObject),
      mTag(tag){

      };

void KilledOnCollideComponent::collision(Level& level, std::shared_ptr<GameObject> obj) {
  if (obj->tag() == mTag && level.state() == STATE_RUNING) {
    std::cout << "kill: obj: " << obj->tag() << " to mTag: " << mTag << std::endl;
    level.lossLive();  //!< set to killed
    // level.removeObject(obj);
  }
};