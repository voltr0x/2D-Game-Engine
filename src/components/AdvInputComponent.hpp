#if !defined(ADV_INPUT_COMPONENT_HPP)
#define ADV_INPUT_COMPONENT_HPP

#include "../Globals.hpp"
#include "../base/PhysicsComponent.hpp"
#include "../base/PhysicsManager.hpp"

class AdvInputComponent : public GenericComponent {
 public:
  inline AdvInputComponent(GameObject& gameObject, float speed)
      : GenericComponent(gameObject),
        mSpeed(speed) {
  }

  inline virtual void update(Level& level) override {
    GameObject& gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

    bool left = INPUT_MANAGER.isKeyDown(SDLK_LEFT);
    bool right = INPUT_MANAGER.isKeyDown(SDLK_RIGHT);
    bool up = INPUT_MANAGER.getInstance().isKeyDown(SDLK_UP);
    bool down = INPUT_MANAGER.getInstance().isKeyDown(SDLK_DOWN);

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

      if (up && !down) {
        gameObject.setGoUp(true);
        gameObject.setGoDown(false);
        pc->setVy(-mSpeed);
        mCount = 0;
      } else if (!up && down) {
        gameObject.setGoUp(false);
        gameObject.setGoDown(true);
        pc->setVy(mSpeed);
        mCount = 0;
      } else {
        if (mCount > 60) {
          gameObject.setGoUp(false);
          gameObject.setGoDown(false);
        }
        mCount++;
        pc->setVy(0.0f);
      }
    }
    if (check) {
      SDL_Log("Game state: %d; Play: left -> %d; right -> %d, debug: %d, state:[%d]",
              level.state(), gameObject.isLeft(), gameObject.isRight(), SETTINGS.debugMode, level.state());
    }
  }

 private:
  float mSpeed;
  int mCount{0};
};

#endif  // ADV_INPUT_COMPONENT_HPP
