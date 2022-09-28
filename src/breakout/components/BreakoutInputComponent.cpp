#include "BreakoutInputComponent.hpp"
#include "../../Globals.hpp"
#include "../../base/PhysicsComponent.hpp"
#include "../../base/PhysicsManager.hpp"

BreakoutInputComponent::BreakoutInputComponent(GameObject& gameObject, float speed, float jump, float gravity)
    : GenericComponent(gameObject),
      mSpeed(speed),
      mJump(jump),
      mGravity(gravity) {
  mCount = 0;
}

void BreakoutInputComponent::update(Level& level) {
  GameObject& gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  // pause handled in level.update()
  bool left = INPUT_MANAGER.isKeyDown(SDLK_LEFT) || INPUT_MANAGER.isKeyDown(SDLK_a);
  bool right = INPUT_MANAGER.isKeyDown(SDLK_RIGHT) || INPUT_MANAGER.isKeyDown(SDLK_d);
  bool jump = INPUT_MANAGER.isKeyPressed(SDLK_UP) || INPUT_MANAGER.isKeyDown(SDLK_j);
  bool reset = INPUT_MANAGER.isKeyPressed(SDLK_r);
  bool start = INPUT_MANAGER.isKeyPressed(SDLK_SPACE);
  bool check = INPUT_MANAGER.isKeyPressed(SDLK_c);
  bool quit = INPUT_MANAGER.isKeyDown(SDLK_q);
  bool debug = INPUT_MANAGER.isKeyPressed(SDLK_SLASH);

  if (debug) {
    SETTINGS.debugMode = !SETTINGS.debugMode;
  }

  pc->addFy(mGravity);

  if (quit) {
    level.setState(STATE_QUIT);
  }
  if (start) {
    if (level.state() == STATE_START) {
      level.setState(STATE_RUNING);
    } else if (level.state() == STATE_KILLED) {
      level.revive();
    }
  }

  //  && level.isGameOver()
  if (reset) {
    level.reset();
  }

  if (level.state() == STATE_RUNING) {
    if (left && !right) {
      gameObject.setLeft(true);
      gameObject.setRight(false);
      pc->setVx(-mSpeed);
      mCount = 0;
    } else if (!left && right) {
      gameObject.setLeft(false);
      gameObject.setRight(true);
      pc->setVx(mSpeed);
      mCount = 0;
    } else {
      if (mCount > 60) {
        gameObject.setLeft(false);
        gameObject.setRight(false);
      }
      mCount++;
      pc->setVx(0.0f);
    }

    gameObject.setJump(true);
    if (jump) {
      mCount = 0;
      bool onGround = false;
      const float inset = gameObject.w() / 10;

      gameObject.setOnGround(onGround);
      std::vector<std::shared_ptr<GameObject>> objects;
      // TODO move PhysicsManager::getInstance() to globals
      if (PhysicsManager::getInstance().getCollisions(gameObject.x() + inset, gameObject.y() + gameObject.h(), gameObject.w() - 2 * inset, 2.0f, objects)) {
        for (auto obj : objects) {
          if (obj->tag() == TAG_BLOCK) {
            onGround = true;
          }
        }
      }
      if (onGround) {
        pc->setVy(-mJump);
        return;
      }
    }
    gameObject.setJump(false);
  } else {
    pc->setVx(0.0f);
  }
  // pc->setVy(std::min(pc->vy() + mGravity, mJump));

  if (check) {
    SDL_Log("Game state: %d; Play: left -> %d; right -> %d, debug: %d, state:[%d]",
            level.state(), gameObject.isLeft(), gameObject.isRight(), SETTINGS.debugMode, level.state());
  }
}