#if !defined(PLATFORMER_INPUT_COMPONENT_HPP)
#define PLATFORMER_INPUT_COMPONENT_HPP

#include "../../Globals.hpp"
#include "../../base/PhysicsComponent.hpp"
#include "../../base/PhysicsManager.hpp"

class PlatformerInputComponent : public GenericComponent {
 public:
  inline PlatformerInputComponent(GameObject& gameObject, float speed, float jump, float gravity)
      : GenericComponent(gameObject),
        mSpeed(speed),
        mJump(jump),
        mGravity(gravity) {
  }

  inline virtual void update(Level& level) override {
    GameObject& gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
    pc->addFy(mGravity);

    bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
    bool jump = InputManager::getInstance().isKeyPressed(SDLK_UP);

    bool reset = INPUT_MANAGER.isKeyPressed(SDLK_r);
    bool start = INPUT_MANAGER.isKeyPressed(SDLK_SPACE);
    bool check = INPUT_MANAGER.isKeyPressed(SDLK_c);
    bool quit = INPUT_MANAGER.isKeyDown(SDLK_q);
    bool debug = INPUT_MANAGER.isKeyPressed(SDLK_SLASH);

    if (debug) {
      SETTINGS.debugMode = !SETTINGS.debugMode;
    }

    if (quit) {
      level.setState(STATE_QUIT);
    }
    if (start) {
      if (level.state() == STATE_START) {
        level.setState(STATE_RUNING);
      } else if (level.state() == STATE_KILLED) {
        level.revive();
        level.setState(STATE_RUNING);
      }
    }
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
        gameObject.setOnGround(onGround);

        const float inset = gameObject.w() / 10;

        std::vector<std::shared_ptr<GameObject>> objects;
        if (PHYSICS_MANAGER.getCollisions(gameObject.x() + inset, gameObject.y() + gameObject.h(), gameObject.w() - 2 * inset, 2.0f, objects)) {
          for (auto obj : objects) {
            if (obj->tag() == TAG_BLOCK) {
              onGround = true;
            }
          }
        }

        if (onGround) {
          pc->setVy(-mJump);
        }
      }
       gameObject.setJump(false);
    } else {
      pc->setVx(0.0f);
    }
    if (check) {
      SDL_Log("Game state: %d; Play: left -> %d; right -> %d, debug: %d, state:[%d]",
              level.state(), gameObject.isLeft(), gameObject.isRight(), SETTINGS.debugMode, level.state());
    }
  }

 private:
  float mSpeed;
  float mJump;
  float mGravity;
  int mCount{0};
};

#endif  // PLATFORMER_INPUT_COMPONENT_HPP
