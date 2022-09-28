#include "BounceOnCollideComponent.hpp"
#include "../../Globals.hpp"

BounceOnCollideComponent::BounceOnCollideComponent(GameObject& gameObject, float speed)
    : GenericComponent(gameObject),
      mSpeed(speed) {
}

void BounceOnCollideComponent::collision(Level& level, std::shared_ptr<GameObject> obj) {
  GameObject& gameObject = getGameObject();

  if ((gameObject.x() + gameObject.w() / 2) <= obj->x()) {
    left = true;
  }
  if ((gameObject.x() + gameObject.w() / 2) >= (obj->x() + obj->w())) {
    left = false;
  }
  if ((gameObject.y() + gameObject.h() / 2) <= obj->y()) {
    up = true;
  }
  if ((gameObject.y() + gameObject.h() / 2) >= (obj->y() + obj->h())) {
    up = false;
  }

  if (obj->tag() == TAG_PLAYER) {
    SDL_Log("hits paddle --- (%f < %f)", (gameObject.y() + gameObject.h() / 2), obj->y());
    // hits paddle
    // hit position on the paddle
    float hitRatio = (gameObject.x() - obj->x()) / obj->w();
    mVx = abs(hitRatio - 0.5) / 0.5 * mSpeed;
    left = hitRatio < 0.5;
  }

  if (obj->tag() >= TAG_BORDER_TOP && obj->tag() <= TAG_BORDER_LEFT) {
    SDL_Log("hits Border --- (%f [%f] < %f [%f])",
            gameObject.y(), (gameObject.y() + gameObject.h() / 2),
            obj->y(), (obj->y() + obj->h()));
  }
};

void BounceOnCollideComponent::update(Level& level) {
  GameObject& gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

  if (level.state() == STATE_RUNING) {
    pc->setVx(left ? -mVx : mVx);
    pc->setVy(up ? -mSpeed : mSpeed);
  }
};